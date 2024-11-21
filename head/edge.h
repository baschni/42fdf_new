/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:05 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 23:34:05 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDGE_H
# define EDGE_H

# include "vector.h"

typedef struct s_edge
{
	t_vect	*start;
	t_vect	*end;
	int		color_start;
	int		color_end;
}	t_edge;

void	free_edges(t_edge **edges);
void	e_free(void *edge);
t_edge	*e_create(t_vect *start, t_vect *end);
t_edge	*e_create3d(double istart[4], double iend[4]);

t_edge	**read_edges_from_map(t_map *map, size_t edges, double z_scale);
int		add_edge_to_array(t_edge **edges, double start[4], double end[4]);

#endif