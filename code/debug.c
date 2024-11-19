/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 16:56:22 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "map.h"
#include "libft.h"
#include "edge.h"
#include "vector.h"
#include "scene.h"

// void	print_map(t_map *map)
// {
// 	int		row;
// 	int		col;
// 	int		*current;

// 	row = 0;
// 	col = 0;
// 	current = map->z;
// 	while (row < map->height)
// 	{
// 		printf("%4i", *current);
// 		if ((++col) == map->width)
// 		{
// 			printf("\n");
// 			row++;
// 		}
// 		if (col == map->width)
// 			col = 0;
// 		current++;
// 	}
// }

/* void	print_edges3d(t_list *edges)
{
	t_edge	*edge;

	while (edges)
	{
		edge = (t_edge *) edges->content;
		printf("(%.0f %.0f %.0f) -> (%.0f %.0f %.0f)\n", v_x(edge->start), \
		v_y(edge->start), v_z(edge->start), v_x(edge->end), \
		v_y(edge->end), v_z(edge->end));
		edges = edges->next;
	}
} */

void	print_edge3d(t_edge *edge)
{
	printf("(%.0f %.0f %.0f) -> (%.0f %.0f %.0f)\n", v_x(edge->start), \
	v_y(edge->start), v_z(edge->start), v_x(edge->end), \
	v_y(edge->end), v_z(edge->end));
}

void	print_edge2d(t_edge *edge)
{
	printf("(%.0f %.0f) -> (%.0f %.0f)\n", v_x(edge->start), \
	v_y(edge->start), v_x(edge->end), v_y(edge->end));
}
// void	print_edges2d(t_list *edges)
// {
// 	t_edge	*edge;

// 	while (edges)
// 	{
// 		edge = (t_edge *) edges->content;

// 		edges = edges->next;
// 	}
// }

void	print_scene(t_scene *scene)
{
	printf("camera\n");
	printf("=============================================\n");
	printf("angle/screen: %.2f %i %i\n", scene->angle / M_PI * 180, \
	scene->width, scene->height);
	printf("position: %.2f %.2f %.2f\n", \
	v_x(scene->pos), v_y(scene->pos), v_z(scene->pos));
	printf("direction: %.2f %.2f %.2f\n", \
	v_x(scene->dir), v_y(scene->dir), v_z(scene->dir));
	printf("orientation_x: %.2f %.2f %.2f\n", \
	v_x(scene->orient_x), v_y(scene->orient_x), v_z(scene->orient_x));
	printf("orientation_y: %.2f %.2f %.2f\n\n", \
	v_x(scene->orient_y), v_y(scene->orient_y), v_z(scene->orient_y));
	printf("center of model: %.2f %.2f %.2f\n", \
	v_x(scene->center), v_y(scene->center), v_z(scene->center));
	printf("initial distance: %.2f\n", scene->initial_distance);
	printf("initial scale: %.2f\n", scene->scale_factor_parallel);
	printf("=============================================\n");
}
