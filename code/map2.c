/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:38:33 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 00:11:21 by baschnit         ###   ########.fr       */
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

void	invert_row_numbers(t_map *map, int height)
{
	t_lrow	*curr;

	curr = map->first_row;
	while (curr)
	{
		curr->content->row = height - curr->content->row - 1;
		curr = curr->next;
	}
}
