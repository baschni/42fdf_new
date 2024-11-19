/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 16:56:25 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "edge.h"
#include "scene.h"
#include "libft.h"
#include "canvas.h"
#include "print_line.h"
#include "mlx.h"
#include "debug.h"

// double ft_abs(double x)
// {
// 	if (x < 0)
// 		return (-1 * x);
// 	else
// 		return (x);
// }

t_vect	*project_point_to_2d(t_vect *point, t_scene *scene)
{
	t_vect	*temp;
	t_vect	*temp2;
	t_vect	*point2d;
	double	scale;
	double	ord;

	if (!set(&point2d, v_empty(2)))
		return (NULL);
	if (!set(&temp2, v_subst(point, scene->pos)))
		return (v_free(point2d), NULL);
	if (!set(&temp, v_proj(temp2, scene->dir, &scale)))
		return (v_free(point2d), v_free(temp2), NULL);
	v_free(temp2);
	scale = scene->width / (tan(scene->angle / 2) * 2 * scale);
	ord = scene->width / 2 + v_mult(temp, scene->orient_x) * scale ;
	v_set_x(point2d, ord);
	ord = scene->height / 2 - v_mult(temp, scene->orient_y) * scale ;
	v_set_y(point2d, ord);
	v_free(temp);
	return (point2d);
}

#include <stdio.h>

t_vect	*project_point_to_2d_parallel(t_vect *point, t_scene *scene)
{
	t_vect	*temp;
	t_vect	*temp2;
	t_vect	*point2d;
	double	scale;
	double	ord;

	if (!set(&point2d, v_empty(2)))
		return (NULL);
	if (!set(&temp2, v_subst(point, scene->pos)))
		return (v_free(point2d), NULL);
	if (!set(&temp, v_proj(temp2, scene->dir, &scale)))
		return (v_free(point2d), v_free(temp2), NULL);
	v_free(temp2);
	ord = v_mult(temp, scene->orient_x) * scene->scale_factor_parallel + scene->width / 2;
	v_set_x(point2d, ord);
	ord = scene->height / 2 - v_mult(temp, scene->orient_y) * scene->scale_factor_parallel;
	v_set_y(point2d, ord);
	//printf("%.2f %.2f\n", v_x(point2d), v_y(point2d));
	v_free(temp);
	return (point2d);
}

t_edge	*project_edge_to_2d(t_edge *edge3d, t_scene *scene)
{
	t_edge	*edge2d;

	if (!set(&edge2d, malloc(sizeof(t_edge))))
		return (NULL);
	if (!set(&(edge2d->start), project_point_to_2d(edge3d->start, scene)))
		return (e_free(edge2d), NULL);
	if (!set(&(edge2d->end), project_point_to_2d(edge3d->end, scene)))
		return (e_free(edge2d), NULL);
	return (edge2d);
}

t_edge	*project_edge_to_2d_parallel(t_edge *edge3d, t_scene *scene)
{
	t_edge	*edge2d;

	if (!set(&edge2d, malloc(sizeof(t_edge))))
		return (NULL);
	if (!set(&(edge2d->start), project_point_to_2d_parallel(edge3d->start, scene)))
		return (e_free(edge2d), NULL);
	if (!set(&(edge2d->end), project_point_to_2d_parallel(edge3d->end, scene)))
		return (e_free(edge2d), NULL);
	return (edge2d);
}

#include <stdio.h>
// t_list	*project_edges_to_viewport(t_list *edges3d, t_scene *scene)
// {
// 	t_list	*mem;
// 	t_edge	*edge3d;
// 	t_list	*edges2d;
// 	t_edge	*edge2d;
// 	t_list	*ledge2d;
// 	int		count;
// 	int		i;

// 	i = 0;
// 	count = ft_lstsize(edges3d);

// 	edges2d = NULL;
// 	mem = NULL;
// 	while (edges3d)
// 	{
// 		stop_time("## next edge", EDGES_LOOP, 1);
// 		printf("%4i/%4i\n", i, count);
// 		i++;
// 		edge3d = (t_edge *) edges3d->content;
// 		stop_time("## extracted edge3d", EDGES_LOOP, 0);
// 		if (!new(&mem, T_EDGE, &edge2d, project_edge_to_2d(edge3d, scene)))
// 			return (auto_free(&mem));
// 		stop_time("## projected edge2d", EDGES_LOOP, 0);
// 		if (!new(&mem, T_LIST_ITEM, &ledge2d, malloc(sizeof(t_list))))
// 			return (auto_free(&mem));
// 		stop_time("## allocated list element edge2d", EDGES_LOOP, 0);
// 		ledge2d->content = edge2d;
// 		ledge2d->next = NULL;
// 		ft_lstadd_front(&edges2d, ledge2d);
// 		stop_time("## added to back of edges", EDGES_LOOP, 0);
// 		edges3d = edges3d->next;
// 	}
// 	free_list_leave_contents(&mem);
// 	return (edges2d);
// }

void	project_edges_to_image(t_edge **edges3d, t_scene *scene, t_canvas *canvas)
{
	t_edge	*edge2d;
	int		count;
	int		i;

	i = 0;
	count = scene->edges / 100;
	if (count == 0)
		count = 10;
	while (*edges3d)
	{
		if (!set(&edge2d, project_edge_to_2d_parallel(*edges3d, scene)))
			return ;
		print_fdf(canvas, edge2d, *edges3d);
		e_free(edge2d);
		if (i % count == 0)
			mlx_put_image_to_window(scene->mlx, scene->mlx_win, canvas->img, 0, 0);
		i++;
		edges3d++;
	}
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, canvas->img, 0, 0);
// 	return (edges2d);
}

void	render_scene(t_scene *scene)
{
	t_canvas	canvas;

	canvas.img = mlx_new_image(scene->mlx, scene->width, scene->height);
	canvas.addr = mlx_get_data_addr(canvas.img, &canvas.bits_per_pixel, \
	&canvas.line_length, &canvas.endian);
	canvas.width = scene->width;
	canvas.height = scene->height;
	//printf("rendering scene %lu\n", scene->edges);
	//print_edges3d(scene->edges3d);
	project_edges_to_image(scene->edges3d, scene, &canvas);
	// edges2d_start = edges2d;
	// edges3d = scene->edges3d;
	// print_edges2d(edges2d);
	// while (edges2d)
	// {
	// 	print_fdf(&canvas, edges2d->content, edges3d->content);
	// 	edges2d = edges2d->next;
	// 	edges3d = edges3d->next;
	// }
	// ft_lstclear(&edges2d_start, &e_free);
	// scene->img = canvas.img;
}
