/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/14 13:04:14 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"
#include "libft.h"
#include "scene.h"
#include "mlx.h"

void	free_map(t_map *map)
{
	ft_lstclear((t_list **) &(map->first_row), free_row);
	free(map);
}

void	free_row(void *vrow)
{
	t_row	*row;

	row = (t_row *) vrow;
	free(row->z);
	free(row->color);
	free(row);
}

void	free_lrow(t_lrow *row)
{
	free_row(row->content);
	free(row);
}

void	free_scene(t_scene *scene)
{
	if (scene->dir)
		v_free(scene->dir);
	if (scene->orient_x)
		v_free(scene->orient_x);
	if (scene->orient_y)
		v_free(scene->orient_y);
	if (scene->pos)
		v_free(scene->pos);
	if (scene->center)
		v_free(scene->center);
	if (scene->edges3d)
		free_edges(scene->edges3d);
	if (scene->img)
		mlx_destroy_image(scene->mlx, scene->img);
	free(scene);
}

void	free_edges(t_edge **edges)
{
	t_edge	**start;

	start = edges;
	while (edges)
	{
		e_free(*edges);
		edges++;
	}
	free(start);
}
