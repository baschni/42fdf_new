/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:02:58 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 23:38:59 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_row
{
	int		row;
	size_t	width;
	int		*z;
	int		*color;
}	t_row;

typedef struct s_lrow
{
	t_row			*content;
	struct s_lrow	*next;
}	t_lrow;

typedef struct s_map
{
	size_t	width;
	size_t	height;
	t_lrow	*first_row;
}	t_map;

t_map	*read_map(char *filename);
void	invert_row_numbers(t_map *map, int height);
void	free_row(void *vrow);
void	free_lrow(t_lrow *row);
void	free_map(t_map *map);

#endif