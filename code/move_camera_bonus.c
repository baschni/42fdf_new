/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:59:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 00:18:39 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "events.h"
#include "scene.h"
#include "render.h"
#include "libft.h"
#include "move_camera_bonus.h"
#include <math.h>
#include <signal.h>

void	zoom(int in_or_out, t_scene *scene)
{
	double	threshold;

	threshold = 0.0146408 * log(0.006064 * scene->edges);
	if (in_or_out && scene->target.cam_dist / SCALE_ON_ZOOM \
	/ scene->initial.cam_dist <= threshold)
		return ;
	pthread_mutex_lock(&(scene->m_view_target));
	if (in_or_out)
	{
		scene->target.scale_parallel = scene->target.scale_parallel \
		* SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
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

void	set_pos_and_center(t_view *view, t_vect *pos, t_vect *center)
{
	view->pos = pos;
	view->center = center;
}

t_vect	*set_dir_side_traversal(t_vect *dir_proj)
{
	t_vect	*temp;
	t_vect	*temp2;

	temp2 = v_new3d(0, 0, 1);
	temp = v_cross_normed(dir_proj, temp2);
	v_free(temp2);
	v_free(dir_proj);
	return (temp);
}

void	traverse_change_target(int in_cam_dir, int forward_or_backward, \
t_vect *dir_proj, t_scene *scene)
{
	if (in_cam_dir)
	{
		if (forward_or_backward)
			set_pos_and_center(&(scene->target), v_subst(scene->target.pos, \
			dir_proj), v_subst(scene->target.center, dir_proj));
		else
			set_pos_and_center(&(scene->target), v_add(scene->target.pos, \
			dir_proj), v_add(scene->target.center, dir_proj));
	}
	else
	{
		dir_proj = set_dir_side_traversal(dir_proj);
		v_ip_scale(scene->target.cam_dist / scene->initial.cam_dist \
		* TRAVERSE, dir_proj);
		if (forward_or_backward)
			set_pos_and_center(&(scene->target), v_subst(scene->target.pos, \
			dir_proj), v_subst(scene->target.center, dir_proj));
		else
			set_pos_and_center(&(scene->target), v_add(scene->target.pos, \
			dir_proj), v_add(scene->target.center, dir_proj));
	}
	v_free (dir_proj);
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
	v_ip_scale(scene->target.cam_dist / scene->initial.cam_dist \
	* TRAVERSE, dir_proj);
	pthread_mutex_lock(&(scene->m_view_target));
	temp_pos = scene->target.pos;
	temp_center = scene->target.center;
	traverse_change_target(in_cam_dir, forward_or_backward, dir_proj, scene);
	v_free (temp_pos);
	v_free (temp_center);
	pthread_mutex_unlock(&(scene->m_view_target));
	render_scene(scene);
}
