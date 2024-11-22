/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:59:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 20:49:19 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "events.h"
#include "scene.h"
#include "render.h"
#include "libft.h"
#include "move_camera_bonus.h"
#include "debug.h"

#include <stdio.h>
#include <math.h>
#include <signal.h>

void	change_projection(t_scene *scene)
{
	pthread_mutex_lock(&(scene->m_view_target));
	if (scene->target.projection_mode == 1)
		scene->target.projection_mode = 0;
	else
		scene->target.projection_mode = 1;
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}

void	reset_view(t_scene *scene)
{
	// if(pthread_mutex_trylock(&(scene->m_is_rendering)))
	// {
	// 	pthread_kill(scene->render_thread, SIGKILL);
	// 	pthread_mutex_lock(&(scene->m_is_rendering));
	// }
	// pthread_mutex_unlock(&(scene->m_is_rendering));
	pthread_mutex_lock(&(scene->m_view_target));
	copy_view(&(scene->initial), &(scene->target));
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}

void	zoom(int in_or_out, t_scene *scene)
{
	double	threshold;

	threshold = 0.0146408 * log(0.004064 * scene->edges);

	if (in_or_out && scene->target.cam_dist / SCALE_ON_ZOOM / scene->initial.cam_dist <= threshold)
		return ;
	pthread_mutex_lock(&(scene->m_view_target));
	if (in_or_out)
	{
		scene->target.scale_parallel = scene->target.scale_parallel * SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
		printf("threshold %f scale normal %f parallel %f edges %lu\n", threshold, scene->target.cam_dist / scene->initial.cam_dist, scene->target.scale_parallel / scene->initial.scale_parallel, scene->edges);
	}
	else
	{
		scene->target.scale_parallel = \
		scene->target.scale_parallel / SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist * SCALE_ON_ZOOM;
	}
	v_free(scene->target.pos);
	set_cam_position(scene, &(scene->target), &(scene->target.pos));
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}

void	traverse(int in_cam_dir, int forward_or_backward, t_scene *scene)
{
	t_vect	*dir_proj;
	t_vect	*temp_pos;
	t_vect	*temp_center;

	dir_proj = v_empty(3);
	v_set_x(dir_proj, v_x(scene->target.dir));
	v_set_y(dir_proj, v_y(scene->target.dir));
	v_ip_norm(dir_proj);
	v_ip_scale(scene->target.cam_dist / scene->initial.cam_dist * TRAVERSE, dir_proj);
	pthread_mutex_lock(&(scene->m_view_target));
	temp_pos = scene->target.pos;
	temp_center = scene->target.center;
	if (in_cam_dir)
	{
		if (forward_or_backward)
		{
			scene->target.pos = v_subst(scene->target.pos, dir_proj);
			scene->target.center = v_subst(scene->target.center, dir_proj);
		}
		else
		{
			scene->target.pos = v_add(scene->target.pos, dir_proj);
			scene->target.center = v_add(scene->target.center, dir_proj);
		}
	}
	else
	{
		dir_proj = v_cross_normed(dir_proj, v_new3d(0, 0, 1));
		v_ip_scale(scene->target.cam_dist / scene->initial.cam_dist * TRAVERSE, dir_proj);
		if (forward_or_backward)
		{
			scene->target.center = v_subst(scene->target.center, dir_proj);
			scene->target.pos = v_subst(scene->target.pos, dir_proj);
		}
		else
		{
			scene->target.pos = v_add(scene->target.pos, dir_proj);
			scene->target.center = v_add(scene->target.center, dir_proj);
		}
	}
	v_free (temp_pos);
	v_free (temp_center);
	v_free (dir_proj);
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}

t_vect	*unrolled_orient_x(t_vect *dir)
{
	t_vect	*temp;
	t_vect	*temp2;

	if (!set(&temp, v_new3d(0, 0, 1)))
		return (NULL);
	if (!set(&temp2, v_cross_normed(dir, temp)))
		return (v_free(temp), NULL);
	v_free(temp);
	return (temp2);
}

t_vect	*v_turn_vect_to_orth_axis(t_vect *x, t_vect *axis, double angle)
{
	double	cosv;
	double	sinv;
	t_vect	*y;

	y = v_cross_normed(axis, x);

	t_vect *temp;

	cosv = cos(angle * M_PI / 180);
	sinv = sin(angle * M_PI / 180);
	v_ip_scale( cosv, x);
	v_ip_scale(sinv, y);
	temp = v_add(x, y);
	return (temp);
}

void	rotate_camera_x_y(int right_or_left, t_scene *scene)
{
	double	x;
	double	y;
	double	cosv;
	double	sinv;
	double	angle;
	t_vect	*temp;

	right_or_left = -(2 * right_or_left - 1);
	cosv = cos(ANGLE_ROLL * M_PI / 180);
	sinv = right_or_left * sin(ANGLE_ROLL * M_PI / 180);

	temp = unrolled_orient_x(scene->target.dir);
	angle = v_angle(scene->target.orient_x, temp, scene->target.dir);

	pthread_mutex_lock(&(scene->m_view_target));
	x = cosv * v_x(scene->target.dir) - sinv * v_y(scene->target.dir);
	y = cosv * v_y(scene->target.dir) + sinv * v_x(scene->target.dir);

	(void) angle;

	printf("%f %f new transl: %f %f\n", v_x(scene->target.dir), v_y(scene->target.dir), x, y);
	print_vector(scene->target.dir, "dir before");
	v_set_x(scene->target.dir, x);
	v_set_y(scene->target.dir, y);
	print_vector(scene->target.dir, "dir after");

	print_vector(scene->target.orient_y, "orient y before");
	print_vector(scene->target.orient_x, "orient x before");

	temp = unrolled_orient_x(scene->target.dir);
	print_vector(scene->target.orient_x, "orient x unrolled");
	v_free(scene->target.orient_x);
	scene->target.orient_x = v_turn_vect_to_orth_axis(temp, scene->target.dir, angle);
	print_vector(scene->target.orient_x, "orient x after");
	v_free(temp);
	v_free(scene->target.orient_y);
	scene->target.orient_y = v_cross(scene->target.orient_x, scene->target.dir);

	printf("angle before %f angle after", angle);

	print_vector(scene->target.pos, "pos before");
	temp = v_scale(scene->target.cam_dist, scene->target.dir);
	scene->target.pos = v_subst(scene->target.center, temp);
	print_vector(scene->target.pos, "pos before");
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}

void	rotate_camera_z(int up_or_down, t_scene *scene)
{
	double		xy;
	double		xy_new;
	double		x;
	double		y;
	double		z;
	double		cosv;
	double		sinv;
	double		angle;
	t_vect		*temp;
	//t_vect	*temp2;
	ft_printf("=================== rotate camera z ===================\n");
	up_or_down = (2 * up_or_down - 1);

	cosv = cos(ANGLE_ROLL * M_PI / 180);
	sinv = up_or_down * sin(ANGLE_ROLL * M_PI / 180);

	x = v_x(scene->target.dir);
	y = v_y(scene->target.dir);
	z = v_z(scene->target.dir);
	xy = sqrt(x * x + y * y);

	temp = unrolled_orient_x(scene->target.dir);
	angle = v_angle(scene->target.orient_x, temp, scene->target.dir);
	v_free(temp);

	print_vector(scene->target.dir, "dir before");
	xy_new = cosv * xy + sinv * z;
	z = cosv * v_z(scene->target.dir) - sinv * xy;
	if (z >= 0.999 || z <= -0.999)
		return ;

	pthread_mutex_lock(&(scene->m_view_target));
	v_set_x(scene->target.dir, x * xy_new / xy);
	v_set_y(scene->target.dir, y * xy_new / xy);
	v_set_z(scene->target.dir, z);

	print_vector(scene->target.dir, "dir after");
	print_vector(scene->target.orient_y, "orient y before");
	print_vector(scene->target.orient_x, "orient x before");

	temp = unrolled_orient_x(scene->target.dir);
	print_vector(scene->target.orient_x, "orient x unrolled");
	v_free(scene->target.orient_x);
	scene->target.orient_x = v_turn_vect_to_orth_axis(temp, scene->target.dir, angle);
	print_vector(scene->target.orient_x, "orient x after");
	v_free(temp);
	v_free(scene->target.orient_y);
	scene->target.orient_y = v_cross(scene->target.orient_x, scene->target.dir);

	printf("angle before %f angle after", angle);
	print_vector(scene->target.orient_y, "orient y after");
	//print_vector(scene->target.orient_x, "orient x after");
	print_vector(scene->target.pos, "pos before");

	temp = v_scale(scene->target.cam_dist, scene->target.dir);
	v_free(scene->target.pos);
	scene->target.pos = v_subst(scene->target.center, temp);
	v_free(temp);
	print_vector(scene->target.pos, "pos after");
	pthread_mutex_unlock(&(scene->m_view_target));

	ft_printf("=================== end rot camera z ===================\n");
	render_scene(scene);
}

void	roll_camera(int right_or_left, t_scene *scene)
{
	t_vect	*temp;
	t_vect	*temp2;
	t_vect	*temp3;
	double	cosv;
	double	sinv;

	right_or_left = (2 * right_or_left - 1);
	cosv = cos(ANGLE_ROLL * M_PI / 180);
	sinv = right_or_left * sin(ANGLE_ROLL * M_PI / 180);
	pthread_mutex_lock(&(scene->m_view_target));
	temp = v_scale(cosv, scene->target.orient_x);
	temp2 = v_scale(-sinv, scene->target.orient_y);
	temp3 = v_add(temp, temp2);
	v_free(temp);
	v_free(temp2);
	temp2 = v_scale(sinv, scene->target.orient_x);
	v_free(scene->target.orient_x);
	scene->target.orient_x = temp3;
	v_ip_norm(scene->target.orient_x);
	temp = v_scale(cosv, scene->target.orient_y);
	temp3 = scene->target.orient_y;
	scene->target.orient_y = v_add(temp, temp2);
	v_ip_norm(scene->target.orient_y);
	v_free(temp);
	v_free(temp2);
	v_free(temp3);

	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}
