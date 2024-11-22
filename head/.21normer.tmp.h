/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .21normer.tmp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:07 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 21:21:16 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _21NORMER_TMP_H
# define _21NORMER_TMP_H

# include <stdio.h>

# include "libft.h"
# include "scene.h"
# include "map.h"

void	print_scene(t_scene *scene);
void	print_edge3d(t_edge *edge);
void	print_edge2d(t_edge *edge);
void	print_vector(t_vect *vect, char *msg);

typedef t_list	t_elist;

#endif