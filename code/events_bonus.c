/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:00:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 14:40:21 by baschnit         ###   ########.fr       */
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
int key_release(int keycode, void *vscene)
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
	else if (keycode == KEY_CODE_I)
		traverse(1, 1, scene);
	else if (keycode == KEY_CODE_K)
		traverse(1, 0, scene);
	else if (keycode == KEY_CODE_J)
		traverse(0, 0, scene);
	else if (keycode == KEY_CODE_L)
		traverse(0, 1, scene);
	else if (keycode == KEY_CODE_P)
		change_projection(scene);
	else if (keycode == KEY_CODE_U)
		change_view_angle(0, scene);
	else if (keycode == KEY_CODE_O)
		change_view_angle(1, scene);
	else if (keycode == KEY_CODE_R)
		reset_view(scene);
	ft_printf("key code%i\n", keycode);
	return (0);
}

int key_press(int keycode, void *vscene)
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
		rotate_camera_z(1, scene);
	else if (keycode == KEY_CODE_S)
		rotate_camera_z(0, scene);
	else if (keycode == KEY_CODE_I)
		traverse(1, 1, scene);
	else if (keycode == KEY_CODE_K)
		traverse(1, 0, scene);
	else if (keycode == KEY_CODE_J)
		traverse(0, 0, scene);
	else if (keycode == KEY_CODE_L)
		traverse(0, 1, scene);
	else if (keycode == KEY_CODE_P)
		change_projection(scene);
	else if (keycode == KEY_CODE_R)
		reset_view(scene);
	// else if (keycode == KEY_CODE_U)
	// 	change_view_angle(0, scene);
	// else if (keycode == KEY_CODE_O)
	// 	change_view_angle(1, scene);
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
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->previous_canvas->img, 0, 0);
	}
	return (0);
}

void	connect_events(t_scene *scene)
{
	mlx_hook(scene->mlx_win, EVENT_CLOSE, 0, &close_window, scene);
	//mlx_key_hook(scene->mlx_win, &key_release, scene);
	mlx_hook(scene->mlx_win, KeyPress, KeyPressMask, &key_press, scene);
	mlx_mouse_hook(scene->mlx_win, &mouse, scene);
	mlx_loop_hook(scene->mlx, &reload_image, scene);
	//mlx_expose_hook(scene->mlx_win, &resize_window, scene);
	ft_printf("events connected\n");
}