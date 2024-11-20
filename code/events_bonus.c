/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:00:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/20 18:48:32 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "events.h"
#include "scene.h"
#include "mlx.h"
#include "render.h"
#include "move_camera_bonus.h"

#include <stdlib.h>


int	close_window(void *vscene)
{
	t_scene	*scene;
	void	*mlx;


	scene = vscene;
	mlx = scene->mlx;
	pthread_mutex_lock(&(scene->m_is_rendering));
	mlx_destroy_window(scene->mlx, scene->mlx_win);
	pthread_mutex_unlock(&(scene->m_is_rendering));
	free_scene(scene);
	mlx_destroy_display(mlx);
	free(mlx);
	exit(0);
	return (0);
}

int key_press(int keycode, void *vscene)
{
	t_scene	*scene;
	
	scene = vscene;
	(void) scene;
	if (keycode == 65307)
		close_window(vscene);
	ft_printf("key code%i\n", keycode);
	return (0);
}

int mouse(int button, int x, int y, void *vscene)
{
	t_scene	*scene;
	
	scene = vscene;
	(void) scene;
	(void) x;
	(void) y;
	ft_printf("mouse button %i\n", button);
	if (button == MOUSE_WHEEL_IN)
		zoom(1, scene);
	else if (button == MOUSE_WHEEL_OUT)
		zoom(0, scene);
	
	return (0);
}

int	resize_window(void *vscene)
{
	t_scene	*scene;
	
	scene = vscene;
	// t_scene	*scene;
	// scene = vscene;
	// mlx_clear_window(scene->mlx, scene->mlx_win);
	// mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img, 0, 0);
	// render_scene(scene);
	(void) scene;
	return (0);
}

int reload_image(void *vscene)
{
	t_scene	*scene;
	
	scene = vscene;
	//(void) scene;
	if(!pthread_mutex_trylock(&(scene->m_canvas)))
	{
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->canvas->img, 0, 0);
		pthread_mutex_unlock(&(scene->m_canvas));
	}
	else
	{
		ft_printf("orig image was blocked");
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->previous_canvas->img, 0, 0);
	}
	return (0);
}

void	connect_events(t_scene *scene)
{
	mlx_hook(scene->mlx_win, EVENT_CLOSE, 0, &close_window, scene);
	mlx_key_hook(scene->mlx_win, &key_press, scene);
	mlx_mouse_hook(scene->mlx_win, &mouse, scene);
	mlx_loop_hook(scene->mlx, &reload_image, scene);
	//mlx_expose_hook(scene->mlx_win, &resize_window, scene);
	ft_printf("events connected\n");
}