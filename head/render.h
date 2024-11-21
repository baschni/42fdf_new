/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:26:59 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 14:45:25 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "libft.h"
# include "scene.h"

void	render_scene(t_scene *scene);
void	*render_thread(void *vscene);
void	init_render(t_scene *scene);

#endif