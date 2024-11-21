/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:32:09 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 00:34:59 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "mlx.h"

int	close_window(void *vscene)
{
	t_scene	*scene;

	scene = vscene;
	pthread_mutex_lock(&(scene->m_is_rendering));
	mlx_loop_end(scene->mlx);
	pthread_mutex_unlock(&(scene->m_is_rendering));
	return (0);
}
