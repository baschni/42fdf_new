/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:26:03 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 00:10:39 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "mlx.h"
#include "move_camera_bonus.h"
#include "vector.h"
#include "scene.h"
#include "libft.h"
#include "render.h"

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
	(v_free(temp), v_free(temp2));
	temp2 = v_scale(sinv, scene->target.orient_x);
	v_free(scene->target.orient_x);
	scene->target.orient_x = temp3;
	v_ip_norm(scene->target.orient_x);
	temp = v_scale(cosv, scene->target.orient_y);
	temp3 = scene->target.orient_y;
	scene->target.orient_y = v_add(temp, temp2);
	v_ip_norm(scene->target.orient_y);
	(v_free(temp), v_free(temp2), v_free(temp3));
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

int	close_window(void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	pthread_mutex_lock(&(scene->m_is_rendering));
	mlx_loop_end(scene->mlx);
	pthread_mutex_unlock(&(scene->m_is_rendering));
	return (0);
}

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
