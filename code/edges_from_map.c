/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_from_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 01:25:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/14 13:29:09 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "map.h"
#include "edge.h"

int	add_edge_to_array(t_edge **edges, double start[4], double end[4])
{
	t_edge	*edge;

	edge = e_create3d(start, end);
	if (!edge)
		return (0);
	*edges = edge;
	return (1);
}

t_edge **add_edges_for_current_coord(t_edge **edges, size_t point[2], int* data[4], double z_scale)
{
	if (point[0] > 0)
	{
		if (!add_edge_to_array(edges, (double [4]){point[0] - 1, \
		point[1], *(data[1] - 1) * z_scale, *(data[3] - 1)}, (double [4]){point[0], \
		point[1], *(data[1]) * z_scale, *(data[3])}))
			return (*edges = NULL, NULL);
		else
			edges++;
	}
	if (!add_edge_to_array(edges, (double [4]){point[0], (point[1] - 1), \
	*(data[0]) * z_scale, *(data[2])}, (double [4]){point[0], \
	point[1], *(data[1]) * z_scale, *(data[3])}))
			return (*edges = NULL, NULL);
	else
		edges++;
	return (edges);
}


t_edge **loop_cols_from_row(t_edge **edges, t_lrow *prev, t_lrow *curr, double z_scale)
{
	int	*z_0;
	int *z_1;
	int *c_0;
	int *c_1;
	size_t col;
	
	col = 0;
	z_0 = prev->content->z;
	z_1 = curr->content->z;
	c_0 = prev->content->color;
	c_1 = curr->content->color;
	while (col < curr->content->width)
	{
		if (!set(&edges, add_edges_for_current_coord(edges, (size_t [2]) {col, \
		curr->content->row}, (int *[4]) { z_0, z_1, c_0, c_1}, z_scale)))
			return (NULL);
		z_0++;
		c_0++;
		z_1++;
		c_1++;
		col++;
	}
	return (edges);
}

t_edge **read_edges_from_map(t_map *map, size_t edge_count, double z_scale)
{
	t_lrow 	*prev;
	t_lrow	*curr;
	t_edge	**edges;
	t_edge	**start;

	if (!set(&edges, malloc(edge_count + 1)))
		return (NULL);
	start = edges;
	prev = map->first_row;
	curr = map->first_row->next;
	while (curr)
	{
		if (!set(edges, loop_cols_from_row(edges, prev, curr, z_scale)))
			return (free_edges(start), NULL);
		prev = curr;
		curr = curr->next;
	}
	*edges = NULL;
	return (start);
}
