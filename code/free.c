/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 14:55:17 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "map.h"
#include "libft.h"
#include "scene.h"
#include "mlx.h"

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
	mlx_destroy_window(scene->mlx, scene->mlx_win);
	free_view(&(scene->initial));
	free_view(&(scene->target));
	free_view(&(scene->render));
	if (scene->edges3d)
		free_edges(scene->edges3d);
	pthread_mutex_destroy(&(scene->m_is_rendering));
	pthread_mutex_destroy(&(scene->m_render_request));
	pthread_mutex_destroy(&(scene->m_view_target));
	pthread_mutex_destroy(&(scene->m_canvas));
	free_canvas(scene->canvas, scene);
	free_canvas(scene->previous_canvas, scene);
	free(scene);
}
