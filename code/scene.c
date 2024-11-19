/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 23:58:40 by baschnit         ###   ########.fr       */
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

t_scene	*adjust_camera_orientation_to_direction(t_scene *scene)
{
	t_vect	*temp;

	if (!set(&temp, v_new3d(0, 0, 1)))
		return (NULL);
	if (v_isparallel(temp, scene->initial.dir))
	{
		if (!set(&(scene->initial.orient_y), v_new3d(0, 1, 0)))
			return (v_free(temp), NULL);
		v_free(temp);
		if (!set(&(scene->initial.orient_x), v_cross(scene->initial.dir, scene->initial.orient_y)))
			return (NULL);
	}
	else
	{
		if (!set(&(scene->initial.orient_x), v_cross_normed(scene->initial.dir, temp)))
			return (v_free(temp), NULL);
		v_free(temp);
		if (!set(&(scene->initial.orient_y), v_cross(scene->initial.orient_x, scene->initial.dir)))
			return (NULL);
	}
	return (scene);
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

int copy_view(t_view *source, t_view *target)
{
	// if (target->pos)
	// 	v_free(target->pos);
	// if (target->dir)
	// 	v_free(target->dir);
	// if (target->orient_x)
	// 	v_free(target->orient_x);
	// if (target->orient_y)
	// 	v_free(target->orient_y);

	target->angle = source->angle;
	target->cam_dist = source->cam_dist;
	target->projection_mode = source->projection_mode;
	target->scale_parallel = source->scale_parallel;
	
	if(!set(&(target->pos),v_dupl(source->pos)))
		return (0);
	if(!set(&(target->dir),v_dupl(source->dir)))
		return (0);
	if(!set(&(target->orient_x),v_dupl(source->orient_x)))
		return (0);
	if(!set(&(target->orient_y),v_dupl(source->orient_y)))
		return (0);
	return (1);
}

void init_view(t_view *view)
{
	view->pos = NULL;
	view->dir = NULL;
	view->orient_x = NULL;
	view->orient_y = NULL;
}

t_scene	*new_scene(t_map *map, int width, int height, double z_scale)
{
	t_scene	*scene;

	if (!set(&scene, malloc(sizeof(t_scene))))
		return (NULL);
	init_view(&(scene->initial));
	init_view(&(scene->target));
	init_view(&(scene->render));
	scene->center = NULL;
	scene->edges3d = NULL;
	scene->width = width;
	scene->height = height;
	scene->initial.angle = INIT_CAM_ANGLE / 180.0 * M_PI;
	scene->edges = ((size_t) map->width - 1) * (size_t) map->height + (size_t) map->width * ((size_t) map->height - 1);
	if (!set(&(scene->initial.dir), \
	v_new3d_normed(INIT_CAM_DIR_X, INIT_CAM_DIR_Y, INIT_CAM_DIR_Z)))
		return (free_scene(scene), NULL);
	if (!adjust_camera_orientation_to_direction(scene))
		return (free_scene(scene), NULL);
	if (!set(&(scene->center), find_center(map, z_scale)))
		return (free_scene(scene), NULL);
	if (!find_cam_position(map, scene, z_scale))
		return (free_scene(scene), NULL);
	return (scene);
}

int init_mutexes(t_scene *scene)
{
	if (!pthread_mutex_init(&(scene->m_is_rendering), NULL))
		return (0);
	if (!pthread_mutex_init(&(scene->m_render_request), NULL))
		return (0);
	if (!pthread_mutex_init(&(scene->m_view_target), NULL))
		return (0);
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
	if (!set(&(scene->edges3d), read_edges_from_map(map, scene->edges, z_scale)))
		return (ft_eprintf(EMSG_READ_EDGES), free_scene(scene), NULL);
	scene->initial.scale_parallel = DBL_MAX;
	if (!set_parallel_scale(&(scene->initial.scale_parallel), scene->edges3d, scene))
		return (ft_eprintf(EMSG_INIT_SCALE_FACTOR), free_scene(scene), NULL);
	scene->initial.projection_mode = 0;
	scene->is_rendering = 0;
	scene->render_request = 0;
	if(!copy_view(&(scene->initial), &(scene->target)))
		return (NULL);
	return (scene);
}

