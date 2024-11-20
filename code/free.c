/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/20 18:54:52 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

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


void free_view(t_view *view)
{
	if (view->dir)
		v_free(view->dir);
	if (view->pos)
		v_free(view->pos);
	if (view->orient_x)
		v_free(view->orient_x);
	if (view->orient_y)
		v_free(view->orient_y);
}

// free_canvas(t_canvas *canvas, void *mlx)
// {
// 		mlx_destroy_image(mlx, canvas->img);
// 		free(canvas->address);
// }

void	free_edges(t_edge **edges)
{
	t_edge	**start;

	start = edges;
	while (*edges)
	{
		e_free(*edges);
		edges++;
	}
	free(start);
}

void	free_scene(t_scene *scene)
{

	free_view(&(scene->initial));
	free_view(&(scene->target));
	free_view(&(scene->render));
	if (scene->center)
		v_free(scene->center);
	if (scene->edges3d)
		free_edges(scene->edges3d);
	// pthread_mutex_destroy(&(scene->m_is_rendering));
	// pthread_mutex_destroy(&(scene->m_render_request));
	// pthread_mutex_destroy(&(scene->m_view_target));
	pthread_mutex_destroy(&(scene->m_canvas));

	free(scene);
}