/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:42:21 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 15:57:30 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"
#include "scene.h"
#include "print_line.h"
#include "debug.h"

#include <stdio.h>
t_vect	*project_point_to_2d(t_vect *point, t_scene *scene)
{
	t_vect	*temp;
	t_vect	*temp2;
	t_vect	*point2d;
	double	scale;
	double	ord;

	if (!set(&point2d, v_empty(2)))
		return (NULL);
	if (!set(&temp2, v_subst(point, scene->render.pos)))
		return (v_free(point2d), NULL);
	if (!set(&temp, v_proj(temp2, scene->render.dir, &scale)))
		return (v_free(point2d), v_free(temp2), NULL);
	scale = fabs(scale);
	v_free(temp2);
	scale = scene->width / (tan(scene->render.angle / 2) * 2 * scale);
	ord = scene->width / 2 + v_mult(temp, scene->render.orient_x) * scale ;
	v_set_x(point2d, ord);
	ord = scene->height / 2 - v_mult(temp, scene->render.orient_y) * scale ;
	v_set_y(point2d, ord);
	v_free(temp);
	return (point2d);
}

t_vect	*project_point_to_2d_parallel(t_vect *point, t_scene *scene)
{
	t_vect	*temp;
	t_vect	*temp2;
	t_vect	*point2d;
	double	scale;
	double	ord;

	if (!set(&point2d, v_empty(2)))
		return (NULL);
	if (!set(&temp2, v_subst(point, scene->render.pos)))
		return (v_free(point2d), NULL);
	if (!set(&temp, v_proj(temp2, scene->render.dir, &scale)))
		return (v_free(point2d), v_free(temp2), NULL);
	v_free(temp2);
	ord = v_mult(temp, scene->render.orient_x) * \
	scene->render.scale_parallel + scene->width / 2;
	v_set_x(point2d, ord);
	ord = scene->height / 2 - v_mult(temp, scene->render.orient_y) \
	* scene->render.scale_parallel;
	v_set_y(point2d, ord);
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
	edge2d->color_start = edge3d->color_start;
	edge2d->color_end = edge3d->color_end;
	return (edge2d);
}

t_edge	*project_edge_to_2d_parallel(t_edge *edge3d, t_scene *scene)
{
	t_edge	*edge2d;

	if (!set(&edge2d, malloc(sizeof(t_edge))))
		return (NULL);
	if (!set(&(edge2d->start), \
	project_point_to_2d_parallel(edge3d->start, scene)))
		return (e_free(edge2d), NULL);
	if (!set(&(edge2d->end), \
	project_point_to_2d_parallel(edge3d->end, scene)))
		return (e_free(edge2d), NULL);
	edge2d->color_start = edge3d->color_start;
	edge2d->color_end = edge3d->color_end;
	return (edge2d);
}

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

void	project_edges_to_image(t_edge **edges3d, \
t_scene *scene, t_canvas *canvas)
{
	t_edge	*edge2d;

	while (*edges3d)
	{
		if (scene->render.projection_mode)
		{
			if (!set(&edge2d, project_edge_to_2d_parallel(*edges3d, scene)))
				return ;
		}
		else
		{
			if (!set(&edge2d, project_edge_to_2d(*edges3d, scene)))
				return ;
		}
		print_fdf(canvas, edge2d);
		e_free(edge2d);
		edges3d++;
	}
}
