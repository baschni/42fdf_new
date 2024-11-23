/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 21:03:23 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "events.h"
#include "edge.h"
#include "scene.h"
#include "libft.h"
#include "canvas.h"
#include "mlx.h"

void	*render_thread(void *vscene)
{
	t_scene		*scene;

	scene = vscene;
	copy_view(&(scene->target), &(scene->render));
	scene->canvas = create_empty_canvas(scene);
	project_edges_to_image(scene->edges3d, scene, scene->canvas);
	return (NULL);
}

void	init_render(t_scene *scene)
{
	render_thread(scene);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, \
		scene->canvas->img, 0, 0);
}
