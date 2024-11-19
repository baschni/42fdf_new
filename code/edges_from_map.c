/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_from_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 01:25:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 16:56:23 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "map.h"
#include "edge.h"
#include "debug.h"

int	add_edge_to_array(t_edge **edges, double start[4], double end[4])
{
	t_edge	*edge;

	// printf("%f %f %f -> %f %f %f", start[0], start[1], start[2], end[0], end[1], end[2]);
	edge = e_create3d(start, end);
	// print_edge3d(edge);
	if (!edge)
		return (0);
	//ft_printf("%p ", edges);
	*edges = edge;
	return (1);
}

int	add_edges_for_current_coord(t_edge ***edges, size_t point[2], int *data[4], double z_scale)
{
	if (point[0] > 0)
	{
		if (!add_edge_to_array(*edges, (double [4]){point[0] - 1, \
		point[1], z_scale * *(data[1] - 1), *(data[3] - 1)}, (double [4]){point[0], \
		point[1], z_scale * *(data[1]), *(data[3])}))
			return (**edges = NULL, 0);
		else
			*edges = *edges + 1;
	}
	if (!add_edge_to_array(*edges, (double [4]){point[0], (point[1] + 1), \
	z_scale* *(data[0]), *(data[2])}, (double [4]){point[0], \
	point[1], z_scale * *(data[1]), *(data[3])}))
		return (**edges = NULL, 0);
	else
		*edges = *edges + 1;
	return (1);
}

int	add_edges_for_first_row_coord(t_edge ***edges, size_t point[2], int *data[2], double z_scale)
{
	if (point[0] > 0)
	{
		if (!add_edge_to_array(*edges, (double [4]){point[0] - 1, \
		point[1], z_scale * *(data[0] - 1), *(data[1] - 1)}, (double [4]){point[0], \
		point[1], z_scale * *(data[0]), *(data[1])}))
			return (**edges = NULL, 0);
		else
			*edges = *edges + 1;
	}
	return (1);
}

int	loop_cols_from_first_row(t_edge ***edges, t_lrow *curr, double z_scale)
{
	int		*z_1;
	int		*c_1;
	size_t	col;

	col = 0;
	z_1 = curr->content->z;
	c_1 = curr->content->color;
	while (col < curr->content->width)
	{
		if (!add_edges_for_first_row_coord(edges, (size_t [2]) {col, \
		curr->content->row}, (int *[2]) { z_1, c_1}, z_scale))
			return (0);
		z_1++;
		c_1++;
		col++;
	}
	return (1);
}

int	loop_cols_from_row(t_edge ***edges, t_lrow *prev, t_lrow *curr, double z_scale)
{
	int		*z_0;
	int		*z_1;
	int		*c_0;
	int		*c_1;
	size_t	col;

	col = 0;
	z_0 = prev->content->z;
	z_1 = curr->content->z;
	c_0 = prev->content->color;
	c_1 = curr->content->color;
	while (col < curr->content->width)
	{
		if (!add_edges_for_current_coord(edges, (size_t [2]) {col, \
		curr->content->row}, (int *[4]) { z_0, z_1, c_0, c_1}, z_scale))
			return (0);
		z_0++;
		c_0++;
		z_1++;
		c_1++;
		col++;
	}
	return (1);
}

t_edge	**read_edges_from_map(t_map *map, size_t edge_count, double z_scale)
{
	t_lrow	*prev;
	t_lrow	*curr;
	t_edge	**edges;
	t_edge	**start;

	if (!set(&edges, malloc((edge_count + 1) * sizeof(t_edge *))))
		return (NULL);
	start = edges;
	prev = map->first_row;
	curr = prev->next;
	ft_printf("%p %p %i\n", start, start + (edge_count + 1), edge_count);
	if (!loop_cols_from_first_row(&edges, prev, z_scale))
		return (free_edges(start), NULL);
	while (curr)
	{
		if (!loop_cols_from_row(&edges, prev, curr, z_scale))
			return (free_edges(start), NULL);
		prev = curr;
		curr = curr->next;
	}
	*(edges) = NULL;
	return (start);
}
