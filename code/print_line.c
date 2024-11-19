/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:43:34 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 23:26:46 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "edge.h"
#include "canvas.h"
#include "print_pixel.h"
#include "mlx.h"

int	blend_color(int start, int end, double progress)
{
	int	r;
	int	g;
	int	b;

	r = (0xFF & start) * (1 - progress) + (0xFF & end ) * progress;
	g = ((0xFF00 & start) >> 2 * 4) * (1 - progress) + ((0xFF00 & end) >> 2 * 4) * progress;
	b = ((0xFF0000 & start) >> 4 * 4) * (1 - progress) + ((0xFF0000 & end) >> 4 * 4) * progress;
	return (((int) round(r)) + (((int) round(g)) << 2 * 4) + (((int) round(b)) << 4 * 4));
}

int	color_from_z(double z)
{
	(void) z;
	// int	color;
	// z = fabs(z);
	// if (0 <= z && z < 1.99)
	// 	color = 0x00FF0000 + (int)(0xFF * (1.9 - z) / 1.99)
	// 	+ (int)(0xFF * (1.99 - z / 2) / 1.99) *16 * 16;
	// else
	// 	color = 0x00FF88FF;
	// return (color);
	return (0x00FFFFFF);
}

void	print_line_x_based(t_canvas *cvs, t_edge *line, t_edge *edge3d, double diff)
{
	int		x;
	double	y;
	double	x0;
	double	y0;
	double	x1;

	x0 = v_x(line->start);
	y0 = v_y(line->start);
	x1 = v_x(line->end);
	x = round(x0);
	while (x != round(x1))
	{
		y = (y0 + (x - x0) * (v_y(line->end) - y0) / (x1 - x0));
		print_pixel_aa_x_based(cvs, x, y, \
		blend_color(edge3d->color_start, edge3d->color_end, (x - x0) / diff));
		if (x0 < x1)
			x++;
		else
			x--;
	}
}

void	print_line_y_based(t_canvas *cvs, t_edge *line, t_edge *edge3d, double diff)
{
	int		y;
	double	x;
	double	y0;
	double	x0;
	double	y1;

	x0 = v_x(line->start);
	y0 = v_y(line->start);
	y1 = v_y(line->end);
	y = round(y0);
	while (y != round(y1))
	{
		x = (x0 + (y - y0) * (v_x(line->end) - x0) / (y1 - y0));
		print_pixel_aa_y_based(cvs, x, y, \
		blend_color(edge3d->color_start, edge3d->color_end, (y - y0) / diff));
		if (y0 < y1)
			y++;
		else
			y--;
	}
}

#include <stdio.h>

void	print_fdf(t_canvas *canvas, t_edge *edge2d, t_edge *edge3d)
{
	double	x_diff;
	double	y_diff;

	x_diff = v_x(edge2d->end) - v_x(edge2d->start);
	y_diff = v_y(edge2d->end) - v_y(edge2d->start);
	printf("print edge 2d, %f %f -> %f %f\n", v_x(edge2d->start), v_y(edge2d->start), v_x(edge2d->end), v_y(edge2d->end));
	if (x_diff == 0 && y_diff == 0)
		print_pixel(canvas, v_x(edge2d->start), v_y(edge2d->start), \
		blend_color(edge3d->color_start, edge3d->color_end, 0.5));
	else if (fabs(x_diff) < fabs(y_diff))
		print_line_y_based(canvas, edge2d, edge3d, y_diff);
	else
		print_line_x_based(canvas, edge2d, edge3d, x_diff);
}

// void	print_fdf(t_canvas *canvas, t_edge *edge2d, t_edge *edge3d)
// {
// 	double	z_diff;
// 	double	x_diff;
// 	double	y_diff;

// 	x_diff = v_x(edge2d->end) - v_x(edge2d->start);
// 	y_diff = v_y(edge2d->end) - v_y(edge2d->start);
// 	z_diff = v_z(edge3d->end) - v_z(edge3d->start);
// 	printf("print edge 2d, %f %f -> %f %f\n", v_x(edge2d->start), v_y(edge2d->start), v_x(edge2d->end), v_y(edge2d->end));
// 	if (x_diff == 0 && y_diff == 0)
// 		print_pixel(canvas, v_x(edge2d->start), v_y(edge2d->start),
// 		color_from_z(v_z(edge3d->start) + z_diff));
// 	else if (fabs(x_diff) < fabs(y_diff))
// 		print_line_y_based(canvas, edge2d, v_z(edge3d->start), z_diff / y_diff);
// 	else
// 		print_line_x_based(canvas, edge2d, v_z(edge3d->start), z_diff / x_diff);
// }