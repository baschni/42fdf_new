/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:00:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 20:17:24 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "events.h"
#include "scene.h"
#include "mlx.h"
#include "render.h"
#include "move_camera_bonus.h"

#include <X11/X.h>
#include <stdlib.h>
#include <unistd.h>

int	reload_image(void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	if (!pthread_mutex_trylock(&(scene->m_canvas)))
	{
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, \
		scene->canvas->img, 0, 0);
		pthread_mutex_unlock(&(scene->m_canvas));
	}
	else
	{
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, \
		scene->previous_canvas->img, 0, 0);
	}
	return (0);
}

void	key_press2(int keycode, t_scene *scene)
{
	if (keycode == KEY_CODE_S)
		rotate_camera_z(0, scene, &(scene->target));
	else if (keycode == KEY_CODE_I)
		traverse(1, 0, scene);
	else if (keycode == KEY_CODE_K)
		traverse(1, 1, scene);
	else if (keycode == KEY_CODE_J)
		traverse(0, 1, scene);
	else if (keycode == KEY_CODE_L)
		traverse(0, 0, scene);
	else if (keycode == KEY_CODE_P)
		change_projection(scene);
	else if (keycode == KEY_CODE_R)
		reset_view(scene);
}

int	key_press(int keycode, void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	(void) scene;
	if (keycode == 65307)
		close_window(vscene);
	else if (keycode == KEY_CODE_E)
		roll_camera(1, scene);
	else if (keycode == KEY_CODE_Q)
		roll_camera(0, scene);
	else if (keycode == KEY_CODE_A)
		rotate_camera_x_y(1, scene);
	else if (keycode == KEY_CODE_D)
		rotate_camera_x_y(0, scene);
	else if (keycode == KEY_CODE_W)
		rotate_camera_z(1, scene, &(scene->target));
	else
		key_press2(keycode, scene);
	return (0);
}

int	mouse(int button, int x, int y, void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	(void) scene;
	(void) x;
	(void) y;
	if (button == MOUSE_WHEEL_IN)
		zoom(1, scene);
	else if (button == MOUSE_WHEEL_OUT)
		zoom(0, scene);
	return (0);
}

void	connect_events(t_scene *scene)
{
	mlx_hook(scene->mlx_win, EVENT_CLOSE, 0, &close_window, scene);
	mlx_hook(scene->mlx_win, KeyPress, KeyPressMask, &key_press, scene);
	mlx_mouse_hook(scene->mlx_win, &mouse, scene);
	mlx_loop_hook(scene->mlx, &reload_image, scene);
}
