/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:59:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/20 23:16:36 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "events.h"
#include "scene.h"
#include "render.h"
#include "libft.h"
#include "move_camera_bonus.h"

#include <stdio.h>
#include <math.h>

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
	
    pthread_mutex_lock(&(scene->m_view_target)); 
	copy_view(&(scene->initial), &(scene->target));
    pthread_mutex_unlock(&(scene->m_view_target)); 
	render_scene(scene);
}

void	zoom(int in_or_out, t_scene *scene)
{
	
    pthread_mutex_lock(&(scene->m_view_target)); 
	if (in_or_out)
	{
		scene->target.scale_parallel = scene->target.scale_parallel * SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
	}
	else
	{
		scene->target.scale_parallel = scene->target.scale_parallel / SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist * SCALE_ON_ZOOM;
	}
	printf("new data: %f %f\n", scene->target.cam_dist, scene->target.scale_parallel);
	if(!set_cam_position(scene, &(scene->target), &(scene->target.pos)))
		close_window(scene);
    pthread_mutex_unlock(&(scene->m_view_target)); 
	render_scene(scene);
}

void	traverse(int in_cam_dir, int forward_or_backward, t_scene *scene)
{
	t_vect *dir_proj;
	
	dir_proj = v_empty(3);
	v_set_x(dir_proj, v_x(scene->target.dir));
	v_set_y(dir_proj, v_y(scene->target.dir));
	dir_proj = v_norm(dir_proj);
	v_ip_scale(scene->initial.cam_dist/20,dir_proj);
	
    pthread_mutex_lock(&(scene->m_view_target)); 
	if (in_cam_dir)
	{
		if(forward_or_backward)
			scene->target.pos = v_subst(scene->target.pos, dir_proj);
		else
			scene->target.pos = v_add(scene->target.pos, dir_proj);
		// scene->target.scale_parallel = scene->target.scale_parallel * SCALE_ON_ZOOM;
		// scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
	}
	else
	{
		dir_proj = v_cross_normed(dir_proj, v_new3d(0, 0, 1));
		v_ip_scale(scene->initial.cam_dist/20,dir_proj);
		if(forward_or_backward)
			scene->target.pos = v_subst(scene->target.pos, dir_proj);
		else
			scene->target.pos = v_add(scene->target.pos, dir_proj);
	}
	// printf("new transl: %f %f\n", scene->target.cam_dist, scene->target.scale_parallel);
	// if(!set_cam_position(scene, &(scene->target), &(scene->target.pos)))
	// 	close_window(scene);
    pthread_mutex_unlock(&(scene->m_view_target)); 
	render_scene(scene);
}

void	roll_camera(int right_or_left, t_scene *scene)
{
	t_vect *temp;
	t_vect *temp2;
	t_vect *temp3;

	right_or_left = - (2 * right_or_left - 1);

	(void) right_or_left;
    pthread_mutex_lock(&(scene->m_view_target)); 
	temp = v_scale(cos(right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_x);
	temp2 = v_scale(sin(-right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_y);
	temp3 = v_add(temp, temp2);
	temp = scene->target.orient_x;
	temp = v_scale(cos(right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_y);
	temp2 = v_scale(sin(right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_x);
	scene->target.orient_y = v_add(temp, temp2);
	scene->target.orient_x = temp3;
    pthread_mutex_unlock(&(scene->m_view_target)); 
	render_scene(scene);
}

void	change_view_angle(int enlarge_or_reduce, t_scene *scene)
{
	t_vect *temp;
	t_vect *temp2;
	t_vect *temp3;

	enlarge_or_reduce = (2 * enlarge_or_reduce - 1);

	(void) right_or_left;
    pthread_mutex_lock(&(scene->m_view_target)); 
	temp = v_scale(cos(right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_x);
	temp2 = v_scale(sin(-right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_y);
	temp3 = v_add(temp, temp2);
	temp = scene->target.orient_x;
	temp = v_scale(cos(right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_y);
	temp2 = v_scale(sin(right_or_left * ANGLE_ROLL * M_PI / 180), scene->target.orient_x);
	scene->target.orient_y = v_add(temp, temp2);
	scene->target.orient_x = temp3;
    pthread_mutex_unlock(&(scene->m_view_target)); 
	render_scene(scene);
}

// void	up_or_down(int in_cam_dir, int forward_or_backward, t_scene *scene)
// {
// 	t_vect *dir_proj;
	
// 	dir_proj = v_empty(3);
// 	v_set_x(dir_proj, v_x(scene->target.dir));
// 	v_set_y(dir_proj, v_y(scene->target.dir));
// 	dir_proj = v_norm(dir_proj);
// 	v_ip_scale(scene->initial.cam_dist/20,dir_proj);
	
//     pthread_mutex_lock(&(scene->m_view_target)); 
// 	if (in_cam_dir)
// 	{
// 		if(forward_or_backward)
// 			scene->target.pos = v_subst(scene->target.pos, dir_proj);
// 		else
// 			scene->target.pos = v_add(scene->target.pos, dir_proj);
// 		// scene->target.scale_parallel = scene->target.scale_parallel * SCALE_ON_ZOOM;
// 		// scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
// 	}
// 	else
// 	{
// 		(void) dir_proj;
// 	}
// 	// printf("new transl: %f %f\n", scene->target.cam_dist, scene->target.scale_parallel);
// 	// if(!set_cam_position(scene, &(scene->target), &(scene->target.pos)))
// 	// 	close_window(scene);
//     pthread_mutex_unlock(&(scene->m_view_target)); 
// 	render_scene(scene);
// }