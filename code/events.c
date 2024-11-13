/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:00:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/13 16:39:00 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	s_free(scene);
	mlx_destroy_display(mlx);
	free(mlx);
	exit(0);
	return (0);
}

int	resize_window(void *vscene)
{
	// t_scene	*scene;
	// scene = vscene;
	// mlx_clear_window(scene->mlx, scene->mlx_win);
	// mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img, 0, 0);
	(void) vscene;
	return (0);
}
