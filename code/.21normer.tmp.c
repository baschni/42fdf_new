/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 00:43:31 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <pthread.h>
#include "events.h"
#include "edge.h"
#include "scene.h"
#include "libft.h"
#include "canvas.h"
#include "debug.h"
#include "mlx.h"

// double ft_abs(double x)
// {
// 	if (x < 0)
// 		return (-1 * x);
// 	else
// 		return (x);
// }

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
	int			ret;

	scene = vscene;
	ft_printf("waiting for mutex m_is_rendering");
	pthread_mutex_lock(&(scene->m_is_rendering));
	ft_printf("rendering scene %lu\n", scene->edges);
	ret = pthread_mutex_lock(&(scene->m_view_target));
	ft_printf("ret thread mutex %i\n", ret);
	copy_view(&(scene->target), &(scene->render));
	pthread_mutex_unlock(&(scene->m_view_target));
	canvas = create_empty_canvas(scene);
	ft_printf("creating canvas %lu\n", scene->edges);
	ft_printf("canvas created %lu\n", scene->edges);
	temp = scene->previous_canvas;
	scene->previous_canvas = scene->canvas;
	project_edges_to_image(scene->edges3d, scene, canvas);
	ft_printf("rendered scene %lu\n", scene->edges);
	pthread_mutex_lock(&(scene->m_canvas));
	scene->canvas = canvas;
	free_canvas(temp, scene);
	pthread_mutex_unlock(&(scene->m_canvas));
	ft_printf("inside thread checking request %i\n", scene->render_request);
	if (scene->render_request)
		return (rerender_image(scene));
	ft_printf("thread is ending %lu\n", scene->edges);
	pthread_mutex_unlock(&(scene->m_is_rendering));
	ft_printf("thread has ended %lu\n", scene->edges);
	return (NULL);
}

void	render_scene(t_scene *scene)
{
	pthread_t	pid;
	int			ret;

	ret = pthread_mutex_trylock(&(scene->m_is_rendering));
	if (!ret)
	{
		pthread_mutex_unlock(&(scene->m_is_rendering));
		pthread_create(&pid, NULL, &render_thread, scene);
		pthread_detach(pid);
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