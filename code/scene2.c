/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:20:01 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/14 13:14:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "config.h"
#include "scene.h"
#include "vector.h"

int	find_min_distance_for_point(double *d_min, double point[3], t_scene *scene)
{
	double	d_point_center;
	double	x;
	double	y;
	t_vect	*temp;
	t_vect	*p_proj;

	if (!set(&p_proj, v_new3d(point[0], point[1], point[2])))
		return (0);
	if (!set(&temp, v_subst(p_proj, scene->center)))
		return (v_free(p_proj), 0);
	v_free(p_proj);
	if (!set(&p_proj, v_proj(temp, scene->dir, &d_point_center)))
		return (v_free(temp), 0);
	v_free(temp);
	x = fabs(v_mult(p_proj, scene->orient_x));
	y = fabs(v_mult(p_proj, scene->orient_y));
	v_free(p_proj);
	x = x / tan(scene->angle / 2) - d_point_center;
	y = y * scene->width / scene->height / tan(scene->angle / 2) \
	- d_point_center;
	if (x > *d_min)
		*d_min = x;
	if (y > *d_min)
		*d_min = y;
	return (1);
}

t_scene	*set_initial_cam_position(t_scene *scene)
{
	t_vect	*temp;

	temp = v_scale(scene->initial_distance, scene->dir);
	if (!temp)
		return (NULL);
	scene->pos = v_subst(scene->center, temp);
	v_free(temp);
	if (!scene->pos)
		return (NULL);
	return (scene);
}

t_scene	*find_cam_position(t_map *map, t_scene *scene, double z_scale)
{
	t_lrow	*i;
	int		*z;
	size_t	col;
	double	d_min;

	d_min = 0;
	i = map->first_row;
	while (i)
	{
		col = 0;
		z = i->content->z;
		while (col < i->content->width)
		{
			if (!find_min_distance_for_point(&d_min, \
			(double [3]){col, i->content->row, *z * z_scale}, scene))
				return (NULL);
			z++;
			col++;
		}
		i = i->next;
	}
	scene->initial_distance = d_min * 1.1;
	return (set_initial_cam_position(scene));
}
