/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 21:01:57 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <pthread.h>
#include "events.h"
#include "edge.h"
#include "scene.h"
#include "libft.h"
#include "canvas.h"
#include "mlx.h"

void	*render_thread(void *vscene);

void	*rerender_image(t_scene *scene)
{
	pthread_mutex_lock(&(scene->m_render_request));
	scene->render_request = 0;
	pthread_mutex_unlock(&(scene->m_render_request));
	pthread_mutex_unlock(&(scene->m_is_rendering));
	render_thread(scene);
	return (NULL);
}

void	*render_thread(void *vscene)
{
	t_scene		*scene;
	t_canvas	*canvas;
	t_canvas	*temp;

	scene = vscene;
	pthread_mutex_lock(&(scene->m_is_rendering));
	pthread_mutex_lock(&(scene->m_view_target));
	copy_view(&(scene->target), &(scene->render));
	pthread_mutex_unlock(&(scene->m_view_target));
	canvas = create_empty_canvas(scene);
	temp = scene->previous_canvas;
	scene->previous_canvas = scene->canvas;
	project_edges_to_image(scene->edges3d, scene, canvas);
	pthread_mutex_lock(&(scene->m_canvas));
	scene->canvas = canvas;
	free_canvas(temp, scene);
	pthread_mutex_unlock(&(scene->m_canvas));
	if (scene->render_request)
		return (rerender_image(scene));
	pthread_mutex_unlock(&(scene->m_is_rendering));
	return (NULL);
}

void	render_scene(t_scene *scene)
{
	int			ret;

	ret = pthread_mutex_trylock(&(scene->m_is_rendering));
	if (!ret)
	{
		pthread_mutex_unlock(&(scene->m_is_rendering));
		pthread_create(&(scene->render_thread), NULL, &render_thread, scene);
		pthread_detach(scene->render_thread);
	}
	else
	{
		pthread_mutex_lock(&(scene->m_render_request));
		scene->render_request = 1;
		pthread_mutex_unlock(&(scene->m_render_request));
	}
}

void	init_render(t_scene *scene)
{
	scene->previous_canvas = create_empty_canvas(scene);
	scene->canvas = create_empty_canvas(scene);
	render_thread(scene);
}
