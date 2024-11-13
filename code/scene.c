/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:37 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "scene.h"
#include "config.h"
#include "map.h"
#include "libft.h"
#include "vector.h"
#include "auto_free_fdf.h"
#include "mlx.h"

t_scene	*adjust_camera_orientation_to_direction(t_scene *scene)
{
	t_list	*mem;
	t_vect	*temp;

	if (!fnew(&mem, T_VECT, &temp, v_new3d(0, 0, 1)))
		return (auto_free(&mem));
	if (v_isparallel(temp, scene->dir))
	{
		if (!new(&mem, T_VECT, &(scene->orient_y), v_new3d(0, 1, 0)))
			return (auto_free(&mem));
		if (!new(&mem, T_VECT, &(scene->orient_x), \
		v_cross(scene->dir, scene->orient_y)))
			return (auto_free(&mem));
	}
	else
	{
		if (!new(&mem, T_VECT, &(scene->orient_x), \
		v_cross_normed(scene->dir, temp)))
			return (auto_free(&mem));
		if (!new(&mem, T_VECT, &(scene->orient_y), \
		v_cross(scene->orient_x, scene->dir)))
			return (auto_free(&mem));
	}
	auto_free_but_two(&mem, scene->orient_x, scene->orient_y);
	return (scene);
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
		ft_lstclear(&scene->edges3d, e_free);
	if (scene->img)
		mlx_destroy_image(scene->mlx, scene->img);
	free(scene);
}

t_vect	*init_vars_find_center(double *len, int *row, int *col)
{
	*len = 0;
	*row = 0;
	*col = 0;
	return (v_empty(3));
}

t_vect	*find_center(t_map *map)
{
	double	len;
	t_vect	*c;
	int		row;
	int		col;
	int		*current;

	c = init_vars_find_center(&len, &row, &col);
	if (!c)
		return (NULL);
	current = map->z;
	while (row < map->height)
	{
		len++;
		*(c->values) += col;
		*(c->values + 1) += (map->height - row - 1);
		*(c->values + 2) += *current * Z_SCALE;
		if ((++col) == map->width)
			row++;
		if (col == map->width)
			col = 0;
		current++;
	}
	if (len == 0)
		return (v_free(c));
	return (v_set3d(c, v_x(c) / len, v_y(c) / len, v_z(c) / len));
}

t_scene	*new_scene(t_map *map, int width, int height)
{
	t_list	*mem;
	t_scene	*scene;

	if (!fnew(&mem, T_SCENE, &scene, malloc(sizeof(t_scene))))
		return (auto_free(&mem));
	scene->dir = NULL;
	scene->pos = NULL;
	scene->orient_x = NULL;
	scene->orient_y = NULL;
	scene->center = NULL;
	scene->edges3d = NULL;
	scene->width = width;
	scene->height = height;
	scene->angle = INIT_CAM_ANGLE / 180.0 * M_PI;
	if (!new(&mem, T_SCENE, &(scene->dir), \
	v_new3d_normed(INIT_CAM_DIR_X, INIT_CAM_DIR_Y, INIT_CAM_DIR_Z)))
		return (auto_free(&mem));
	if (!adjust_camera_orientation_to_direction(scene))
		return (auto_free(&mem));
	if (!new(&mem, T_VECT, &(scene->center), find_center(map)))
		return (auto_free(&mem));
	if (!find_cam_position(map, scene))
		return (auto_free(&mem));
	free_list_leave_contents(&mem);
	return (scene);
}
