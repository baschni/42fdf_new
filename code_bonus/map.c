/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:20:24 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 21:15:26 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "map.h"
#include "libft.h"

int	read_coord_and_color(long *nbr, long *clr, char *info)
{
	char	**pair;

	if (!ft_strchr(info, SEPARATOR_COLOR))
	{
		*nbr = ft_atol(info);
		if (!ft_is_int_str(info) || *nbr > INT_MAX || *nbr < INT_MIN)
			return (ft_eprintf(EMSG_WRONG_Z_FORMAT), 0);
		*clr = DEFAULT_COLOR;
		return (1);
	}
	if (!set(&pair, ft_split(info, SEPARATOR_COLOR)))
		return (ft_eprintf(EMSG_MEM), 0);
	if (ft_count_splits(pair) != 2)
		return (ft_eprintf(EMSG_WRONG_COMMA), ft_free_splits(pair), 0);
	*nbr = ft_atol(*pair);
	if (ft_is_hex_str(*(pair + 1)))
		*clr = ft_htol(*(pair + 1) + 2);
	else
		*clr = ft_atol(*(pair + 1));
	if (!ft_is_int_str(*pair) || *nbr > INT_MAX || *nbr < INT_MIN)
		return (ft_free_splits(pair), ft_eprintf(EMSG_WRONG_Z_FORMAT), 0);
	if (!(ft_is_hex_str(*(pair + 1)) || ft_is_int_str(*(pair + 1))) \
	|| *clr > INT_MAX || *clr < 0)
		return (ft_free_splits(pair), ft_eprintf(EMSG_WRONG_C_FORMAT), 0);
	return (ft_free_splits(pair), 1);
}

int	read_row_values(char **splits, t_row *row)
{
	long	nbr;
	long	clr;
	int		*n;
	int		*c;

	n = row->z;
	c = row->color;
	while (*splits)
	{
		if (!read_coord_and_color(&nbr, &clr, *splits))
			return (0);
		*n = (int) nbr;
		*c = (int) clr;
		n++;
		c++;
		splits++;
	}
	return (1);
}

t_lrow	*read_line_to_row(char *line, int prev_row)
{
	t_row	*row;
	t_lrow	*lrow;
	char	**splits;

	ft_cancel_newline_at_end(line);
	if (!set(&row, malloc(sizeof(t_row))))
		return (ft_eprintf(EMSG_MEM), NULL);
	row->row = prev_row + 1;
	if (!set(&splits, ft_split(line, SEPARATOR_COORD)))
		return (ft_eprintf(EMSG_MEM), free_row(row), NULL);
	row->width = ft_count_splits(splits);
	if (!set(&(row->z), malloc(sizeof(int) * row->width)))
		return (ft_eprintf(EMSG_MEM), ft_free_splits(splits), free(row), NULL);
	if (!set(&(row->color), malloc(sizeof(int) * row->width)))
		return (ft_eprintf(EMSG_MEM), ft_free_splits(splits), \
		free(row->z), free(row), NULL);
	if (!read_row_values(splits, row))
		return (ft_free_splits(splits), free_row(row), NULL);
	ft_free_splits(splits);
	if (!set(&lrow, ft_lstnew(row)))
		return (free_row(row), NULL);
	return (lrow);
}

int	read_lines_to_map(int fd, t_map *map)
{
	t_lrow	*curr;
	t_lrow	*prev;
	char	*line;

	if (!set(&line, get_next_line(fd)))
		return (ft_eprintf(EMSG_EMPTY_FILE), 0);
	if (!set(&(map->first_row), read_line_to_row(line, -1)))
		return (free(line), 0);
	free(line);
	prev = map->first_row;
	map->width = map->first_row->content->width;
	while (set(&line, get_next_line(fd)))
	{
		if (!set(&curr, read_line_to_row(line, prev->content->row)))
			return (free(line), 0);
		free(line);
		if (curr->content->width != map->width)
			return (ft_eprintf(EMSG_DIFFERENT_WIDTH), free_lrow(curr), 0);
		if (curr->content->width == 0)
			return (ft_eprintf(EMSG_EMPTY_LINE), free_lrow(curr), 0);
		prev->next = curr;
		prev = curr;
	}
	return (1);
}

t_map	*read_map(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_eprintf(EMSG_FILE), NULL);
	if (!set(&map, malloc(sizeof(t_map))))
		return (ft_eprintf(EMSG_MEM), close(fd), NULL);
	map->width = -1;
	map->first_row = (NULL);
	if (!read_lines_to_map(fd, map))
		return (free_map(map), close(fd), NULL);
	close (fd);
	map->height = (size_t) ft_lstsize((t_list *) map->first_row);
	if (map->height == 0)
		return (ft_eprintf(EMSG_FILE), free_map(map), NULL);
	if (map->width == 1 && map->height == 1)
		return (ft_eprintf(EMSG_POINT), free_map(map), NULL);
	if ((map->height - 1) > ((SIZE_MAX / (map->width - 1)) - 1) / 2)
		return (ft_eprintf(EMSG_SIZE_MAX), free_map(map), NULL);
	invert_row_numbers(map, map->height);
	return (map);
}
