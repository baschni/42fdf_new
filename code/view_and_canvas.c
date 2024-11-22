/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_and_canvas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:36:05 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 19:33:53 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mlx.h"

void	init_view(t_view *view)
{
	view->pos = NULL;
	view->dir = NULL;
	view->orient_x = NULL;
	view->orient_y = NULL;
	view->center = NULL;
}

int	copy_view(t_view *source, t_view *target)
{
	target->angle = source->angle;
	target->cam_dist = source->cam_dist;
	target->projection_mode = source->projection_mode;
	target->scale_parallel = source->scale_parallel;
	if (target->center)
		v_free(target->center);
	if (!set(&(target->center), v_dupl(source->center)))
		return (0);
	if (target->pos)
		v_free(target->pos);
	if (!set(&(target->pos), v_dupl(source->pos)))
		return (0);
	if (target->dir)
		v_free(target->dir);
	if (!set(&(target->dir), v_dupl(source->dir)))
		return (0);
	if (target->orient_y)
		v_free(target->orient_y);
	if (!set(&(target->orient_y), v_dupl(source->orient_y)))
		return (0);
	if (target->orient_x)
		v_free(target->orient_x);
	if (!set(&(target->orient_x), v_dupl(source->orient_x)))
		return (0);
	return (1);
}

void	free_view(t_view *view)
{
	if (view->dir)
		v_free(view->dir);
	if (view->pos)
		v_free(view->pos);
	if (view->center)
		v_free(view->center);
	if (view->orient_x)
		v_free(view->orient_x);
	if (view->orient_y)
		v_free(view->orient_y);
}

t_canvas	*create_empty_canvas(t_scene *scene)
{
	t_canvas	*canvas;

	canvas = malloc(sizeof(t_canvas));
	canvas->img = mlx_new_image(scene->mlx, scene->width, scene->height);
	canvas->addr = mlx_get_data_addr(canvas->img, &(canvas->bits_per_pixel), \
	&(canvas->line_length), &(canvas->endian));
	canvas->width = scene->width;
	canvas->height = scene->height;
	return (canvas);
}

void	free_canvas(t_canvas *canvas, t_scene *scene)
{
	mlx_destroy_image(scene->mlx, canvas->img);
	free(canvas);
}
