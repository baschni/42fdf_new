/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:26:03 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 00:12:05 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "move_camera_bonus.h"
#include "vector.h"
#include "scene.h"
#include "libft.h"
#include "render.h"

t_vect	*v_turn_vect_to_orth_axis(t_vect *x, t_vect *axis, double angle)
{
	double	cosv;
	double	sinv;
	t_vect	*y;
	t_vect	*temp;

	y = v_cross_normed(axis, x);
	cosv = cos(angle * M_PI / 180);
	sinv = sin(angle * M_PI / 180);
	v_ip_scale(cosv, x);
	v_ip_scale(sinv, y);
	temp = v_add(x, y);
	v_free(y);
	return (temp);
}

void	rotate_x_y_set_dir(t_vect *dir, double cosv, double sinv)
{
	double	x;
	double	y;

	x = cosv * v_x(dir) - sinv * v_y(dir);
	y = cosv * v_y(dir) + sinv * v_x(dir);
	v_set_x(dir, x);
	v_set_y(dir, y);
}

void	rotate_camera_x_y(int right_or_left, t_scene *scene)
{
	double	angle;
	t_vect	*temp;

	right_or_left = -(2 * right_or_left - 1);
	temp = unrolled_orient_x(scene->target.dir);
	angle = v_angle(scene->target.orient_x, temp, scene->target.dir);
	v_free(temp);
	pthread_mutex_lock(&(scene->m_view_target));
	rotate_x_y_set_dir(scene->target.dir, cos(ANGLE_ROLL * M_PI / 180), \
	right_or_left * sin(ANGLE_ROLL * M_PI / 180));
	temp = unrolled_orient_x(scene->target.dir);
	v_free(scene->target.orient_x);
	scene->target.orient_x = v_turn_vect_to_orth_axis(temp, \
	scene->target.dir, angle);
	v_free(temp);
	v_free(scene->target.orient_y);
	scene->target.orient_y = v_cross(scene->target.orient_x, scene->target.dir);
	temp = v_scale(scene->target.cam_dist, scene->target.dir);
	v_free(scene->target.pos);
	scene->target.pos = v_subst(scene->target.center, temp);
	v_free(temp);
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}

int	rotate_z_set_z(t_vect *dir, double cosv, double sinv)
{
	double	xy;
	double	xy_new;
	double	x;
	double	y;
	double	z;

	x = v_x(dir);
	y = v_y(dir);
	z = v_z(dir);
	xy = sqrt(x * x + y * y);
	xy_new = cosv * xy + sinv * z;
	z = cosv * v_z(dir) - sinv * xy;
	if (z >= 0.999 || z <= -0.999)
		return (0);
	v_set_x(dir, x * xy_new / xy);
	v_set_y(dir, y * xy_new / xy);
	v_set_z(dir, z);
	return (1);
}

void	rotate_camera_z(int up_or_down, t_scene *scene, t_view *view)
{
	double	angle;
	t_vect	*temp;

	up_or_down = (2 * up_or_down - 1);
	temp = unrolled_orient_x(view->dir);
	angle = v_angle(view->orient_x, temp, view->dir);
	v_free(temp);
	pthread_mutex_lock(&(scene->m_view_target));
	if (!rotate_z_set_z(view->dir, cos(ANGLE_ROLL * M_PI / 180), \
	up_or_down * sin(ANGLE_ROLL * M_PI / 180)))
		return (pthread_mutex_unlock(&(scene->m_view_target)), (void) 1);
	temp = unrolled_orient_x(scene->target.dir);
	v_free(view->orient_x);
	view->orient_x = v_turn_vect_to_orth_axis(temp, view->dir, angle);
	v_free(temp);
	v_free(view->orient_y);
	view->orient_y = v_cross(view->orient_x, view->dir);
	temp = v_scale(scene->target.cam_dist, view->dir);
	v_free(view->pos);
	view->pos = v_subst(view->center, temp);
	v_free(temp);
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}
