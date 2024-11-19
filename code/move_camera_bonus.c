/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:59:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 22:21:01 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "events.h"
#include "scene.h"
#include "render.h"
#include "libft.h"

#include <stdio.h>

void	zoom(int in_or_out, t_scene *scene)
{
	if (in_or_out)
	{
		scene->target.scale_parallel = scene->target.scale_parallel * SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist * SCALE_ON_ZOOM;
	}
	else
	{
		scene->target.scale_parallel = scene->target.scale_parallel / SCALE_ON_ZOOM;
		scene->target.cam_dist = scene->target.cam_dist / SCALE_ON_ZOOM;
	}
	if(!set_cam_position(scene, scene->target.pos))
		close_window(scene);
	render_scene(scene);
}
