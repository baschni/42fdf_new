/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 22:20:30 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <pthread.h>

# include "vector.h"
# include "map.h"
# include "edge.h"
# include "libft.h"

typedef struct s_view
{
	double			angle;
	t_vect			*dir;
	t_vect			*orient_x;
	t_vect			*orient_y;
	t_vect			*pos;
	
	double			cam_dist;
	double			scale_parallel;
	int				projection_mode;
}	t_view;

typedef struct s_scene
{
	void			*mlx;
	void			*mlx_win;
	unsigned int	width;
	unsigned int	height;
	size_t			edges;

	t_view			initial;
	t_view			render;
	t_view			target;
	
	t_vect			*center;
	
	int is_rendering;
	int render_request;
	
	pthread_mutex_t m_is_rendering;
	pthread_mutex_t m_render_request;

	t_edge			**edges3d;
	void			*img;
}	t_scene;

t_scene	*init_scene(t_map *map, void *mlx, double z_scale);
t_scene	*new_scene(t_map *map, int width, int height, double z_scale);
t_scene	*find_cam_position(t_map *map, t_scene *scene, double z_scale);
t_scene	*set_cam_position(t_scene *scene, t_vect *pos);
int copy_view(t_view *source, t_view *target);
int		set_parallel_scale(double *scale, t_edge **edges, t_scene *scene);
void	free_scene(t_scene *scene);
t_edge **read_edges_from_map(t_map *map, size_t edges, double z_scale);

#endif