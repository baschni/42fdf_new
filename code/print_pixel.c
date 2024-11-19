/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 06:17:00 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/22 06:40:10 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"
#include "math.h"

int	adjust_color(double ratio, int color)
{
	int	opacity_r;
	int	opacity_g;
	int	opacity_b;

	opacity_r = round(((int)(((color & 0x00FF0000) >> 4 * 4) \
	* (1 - ratio))) << 4 * 4);
	opacity_g = round(((int)(((color & 0x0000FF00) >> 2 * 4) \
	* (1 - ratio))) << 2 * 4);
	opacity_b = round(((int)(((color & 0x000000FF) >> 0 * 4) \
	* (1 - ratio))) << 0 * 4);
	return (opacity_r + opacity_g + opacity_b);
}

void	print_pixel(t_canvas *img, int x, int y, int color)
{
	void	*dst;

	if (x < 0 || y < 0 || x > img->width || y > img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	print_pixel_aa_x_based(t_canvas *img, int x, double y, int color)
{
	int	yh;
	int	yl;

	yl = floor(y);
	yh = ceil(y);
	if (yl == yh)
		print_pixel(img, x, yl, color);
	else
	{
		print_pixel(img, x, yl, adjust_color((y - yl), color));
		print_pixel(img, x, yh, adjust_color((yh - y), color));
	}
}

void	print_pixel_aa_y_based(t_canvas *img, double x, int y, int color)
{
	int	xh;
	int	xl;

	xl = floor(x);
	xh = ceil(x);
	if (xl == xh)
		print_pixel(img, xl, y, color);
	else
	{
		print_pixel(img, xl, y, adjust_color((x - xl), color));
		print_pixel(img, xh, y, adjust_color((xh - x), color));
	}
}
