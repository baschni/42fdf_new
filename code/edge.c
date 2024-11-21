/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 23:36:32 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edge.h"
#include "vector.h"

#include <stdlib.h>

void	e_free(void *vedge)
{
	t_edge	*edge;

	edge = (t_edge *) vedge;
	v_free(edge->start);
	v_free(edge->end);
	free(edge);
}

t_edge	*e_create(t_vect *start, t_vect *end)
{
	t_edge	*edge;

	edge = malloc(sizeof(t_edge));
	edge->start = start;
	edge->end = end;
	return (edge);
}

t_edge	*e_create3d(double istart[4], double iend[4])
{
	t_vect	*start;
	t_vect	*end;
	t_edge	*edge;

	start = v_new3d(istart[0], istart[1], istart[2]);
	if (!start)
		return (NULL);
	end = v_new3d(iend[0], iend[1], iend[2]);
	if (!end)
	{
		v_free(start);
		return (NULL);
	}
	edge = e_create(start, end);
	if (!edge)
	{
		v_free(start);
		v_free(end);
		return (NULL);
	}
	edge->color_start = istart[3];
	edge->color_end = iend[3];
	return (edge);
}

int	add_edge_to_array(t_edge **edges, double start[4], double end[4])
{
	t_edge	*edge;

	edge = e_create3d(start, end);
	if (!edge)
		return (0);
	*edges = edge;
	return (1);
}
