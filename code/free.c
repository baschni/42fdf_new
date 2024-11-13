/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:12:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/13 16:41:01 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"
#include "libft.h"

void	free_map(t_map *map)
{
	ft_lstclear((t_list **) &(map->first_row), free_row);
	free(map);
}

void	free_row(void	*vrow)
{
	t_row	*row;

	row = (t_row *) vrow;
	free(row->z);
	free(row->color);
	free(row);
}

void	free_lrow(t_lrow *row)
{
	free_row(row->content);
	free(row);
}
