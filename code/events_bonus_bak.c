/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:00:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 17:33:57 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "events.h"
#include "scene.h"
#include "mlx.h"
#include "render.h"

#include <stdlib.h>


int	close_window(void *vscene)
{
	t_scene	*scene;
	void	*mlx;

	scene = vscene;
	mlx = scene->mlx;
	mlx_destroy_window(scene->mlx, scene->mlx_win);
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
	if (keycode == )
	ft_printf("key code%i\n", keycode);
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

void	connect_events(t_scene *scene)
{
	mlx_hook(scene->mlx_win, EVENT_CLOSE, 0, &close_window, scene);
	mlx_key_hook(scene->mlx_win, &key_press, scene);
	mlx_expose_hook(scene->mlx_win, &resize_window, scene);
}