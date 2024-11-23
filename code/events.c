/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:00:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 21:03:20 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "events.h"
#include "scene.h"
#include "mlx.h"
#include "render.h"
#include "move_camera_bonus.h"

#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

int	close_window(void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	mlx_loop_end(scene->mlx);
	return (0);
}

int	reload_image(void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, \
	scene->canvas->img, 0, 0);
	return (0);
}

int	key_press(int keycode, void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	(void) scene;
	if (keycode == 65307)
		close_window(vscene);
	return (0);
}

void	connect_events(t_scene *scene)
{
	mlx_hook(scene->mlx_win, EVENT_CLOSE, 0, &close_window, scene);
	mlx_hook(scene->mlx_win, KeyPress, KeyPressMask, &key_press, scene);
	mlx_loop_hook(scene->mlx, &reload_image, scene);
}
