/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 23:36:21 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "scene.h"
#include "config.h"
#include "map.h"
#include "libft.h"
#include "vector.h"
#include "mlx.h"
#include "limits.h"
#include "float.h"

t_view	*adjust_camera_orientation_to_direction(t_view *view)
{
	t_vect	*temp;

	if (!set(&temp, v_new3d(0, 0, 1)))
		return (NULL);
	if (v_isparallel(temp, view->dir))
	{
		if (!set(&(view->orient_y), v_new3d(0, 1, 0)))
			return (v_free(temp), NULL);
		v_free(temp);
		if (!set(&(view->orient_x), v_cross(view->dir, view->orient_y)))
			return (NULL);
	}
	else
	{
		if (!set(&(view->orient_x), v_cross_normed(view->dir, temp)))
			return (v_free(temp), NULL);
		v_free(temp);
		if (!set(&(view->orient_y), v_cross(view->orient_x, view->dir)))
			return (NULL);
	}
	return (view);
}

t_vect	*find_center(t_map *map, double z_scale)
{
	t_vect	*c;
	t_lrow	*i;
	int		*z;
	size_t	col;

	i = map->first_row;
	if (!set(&c, v_empty(3)))
		return (NULL);
	while (i)
	{
		col = 0;
		z = i->content->z;
		while (col < i->content->width)
		{
			*(c->values) += col;
			*(c->values + 1) += i->content->row;
			*(c->values + 2) += *z * z_scale;
			z++;
			col++;
		}
		i = i->next;
	}
	v_ip_scale(1. / map->width / map->height, c);
	return (c);
}

t_scene	*new_scene(t_map *map, int width, int height, double z_scale)
{
	t_scene	*scene;

	if (!set(&scene, malloc(sizeof(t_scene))))
		return (NULL);
	init_view(&(scene->initial));
	init_view(&(scene->target));
	init_view(&(scene->render));
	scene->edges3d = NULL;
	scene->width = width;
	scene->height = height;
	scene->initial.angle = INIT_CAM_ANGLE / 180.0 * M_PI;
	scene->edges = ((size_t) map->width - 1) * (size_t) map->height \
	+ (size_t) map->width * ((size_t) map->height - 1);
	if (!set(&(scene->initial.dir), \
	v_new3d_normed(INIT_CAM_DIR_X, INIT_CAM_DIR_Y, INIT_CAM_DIR_Z)))
		return (free_scene(scene), NULL);
	if (!adjust_camera_orientation_to_direction(&(scene->initial)))
		return (free_scene(scene), NULL);
	if (!set(&(scene->initial.center), find_center(map, z_scale)))
		return (free_scene(scene), NULL);
	if (!find_cam_position(map, scene, z_scale))
		return (free_scene(scene), NULL);
	return (scene);
}

int	init_mutexes(t_scene *scene)
{
	if (pthread_mutex_init(&(scene->m_is_rendering), NULL))
		return (0);
	if (pthread_mutex_init(&(scene->m_render_request), NULL))
		return (0);
	if (pthread_mutex_init(&(scene->m_canvas), NULL))
		return (0);
	if (pthread_mutex_init(&(scene->m_view_target), NULL))
		return (0);
	ft_printf("mutexes initalisied\n");
	return (1);
}

t_scene	*init_scene(t_map *map, void *mlx, double z_scale)
{
	t_scene	*scene;
	int		screen_width;
	int		screen_height;

	mlx_get_screen_size(mlx, &screen_width, &screen_height);
	screen_width = round(screen_width * INITIAL_SCREEN_COVER);
	screen_height = round(screen_height * INITIAL_SCREEN_COVER);
	if (!set(&scene, new_scene(map, screen_width, screen_height, z_scale)))
		return (ft_eprintf(EMSG_SCENE_INIT), NULL);
	scene->mlx = mlx;
	if (!set(&(scene->edges3d), \
	read_edges_from_map(map, scene->edges, z_scale)))
		return (ft_eprintf(EMSG_READ_EDGES), free_scene(scene), NULL);
	scene->initial.scale_parallel = DBL_MAX;
	if (!set_parallel_scale(&(scene->initial.scale_parallel), \
	scene->edges3d, scene))
		return (ft_eprintf(EMSG_INIT_SCALE_FACTOR), free_scene(scene), NULL);
	scene->initial.projection_mode = 0;
	scene->is_rendering = 0;
	scene->render_request = 0;
	if (!copy_view(&(scene->initial), &(scene->target)))
		return (free_scene(scene), NULL);
	if (!init_mutexes(scene))
		return (free_scene(scene), NULL);
	return (scene);
}
