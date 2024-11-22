/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:56:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/23 00:18:46 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "config.h"
#include "map.h"
#include "scene.h"
#include "render.h"
#include "mlx.h"
#include "events.h"

void	free_mlx(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
}

/**
 * @brief will read the map file, start mlx and output edges to the window
 *
 * The main function will read the map file, start an mlx framework and
 * initialise the scene. The scene object is the central structure holding all
 * necessary data (mlx, mlx_window, edges, camera configuration).
 *
 * After initialisation the events will be connected and the scene rendered to
 * the window. Finally the mlx loop is started. To free the memory at the end of
 *  the program, the respective actions will be defined in the close event.
 *
 * @param argc	Number of arguments on the command line
 * @param argv	string array of the arguments
 * @return int	return value of main, 0 in case of success (never reached), 
 * 				1 in case of error
*/

int	main(int argc, char *argv[])
{
	t_map	*map;
	t_scene	*scene;
	void	*mlx;
	void	*mlx_win;

	if (argc != 2)
		return (ft_printf("usage: %s <filename>\n", PROGRAM_NAME), 0);
	if (!set(&map, read_map(argv[1])))
		return (1);
	if (!set(&mlx, mlx_init()))
		return (free_map(map), 1);
	if (!set(&scene, init_scene(map, mlx, Z_SCALE)))
		return (free_map(map), free_mlx(mlx), 1);
	free_map(map);
	if (!set(&mlx_win, mlx_new_window(mlx, scene->width, \
	scene->height, PROGRAM_NAME)))
		return (free_map(map), free_scene(scene), free_mlx(mlx), 1);
	scene->mlx_win = mlx_win;
	connect_events(scene);
	init_render(scene);
	mlx_loop(mlx);
	free_scene(scene);
	mlx_destroy_display(mlx);
	return (free(mlx), 0);
}
