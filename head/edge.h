/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:05 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/14 13:25:59 by baschnit         ###   ########.fr       */
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

#endif