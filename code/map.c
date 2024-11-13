/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:20:24 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/13 15:28:37 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <limits.h>

#include "config.h"
#include "map.h"
#include "libft.h"

t_map	*read_map(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!set(&map, malloc(sizeof(t_map))))
		return (ft_eprintf(EMSG_MEM), close(fd), NULL);
	map->width = -1;
	map->first_row = (NULL);
	if (!read_lines_to_map(fd, map))
		return (free_map(map), close(fd), NULL);
	close (fd);
	map->height = ft_lstsize(map->first_row);
	if (map->height == 0)
		return (ft_eprintf(EMSG_FILE), free_map(map), NULL);
	if (map->width == 1 && map->height == 1)
		return (ft_eprintf(EMSG_POINT), free_map(map), NULL);
	if (map->width * map->height > SIZE_MAX)
		return (ft_eprintf(EMSG_SIZE_MAX), free_map(map), NULL);
	return (map);
}

int	read_lines_to_map(int fd, t_map *map)
{
	t_row	*curr;
	t_row	*prev;
	char	*line;

	line = get_next_line(fd);
	if (!set(&(map->first_row), read_line_to_row(line, 0)))
		return (free(line), 0);
	prev = map->first_row;
	map->width = map->first_row->width;
	while (line)
	{
		if (!set(&curr, read_line_to_row(line, prev->row)))
			return (free(line), 0);
		free(line);
		if (curr->width != map->width)
			return (ft_eprintf(EMSG_DIFFERENT_WIDTH), free_row(curr), 0);
		if (curr->width == 0)
			return (ft_eprintf(EMSG_EMPTY_LINE), free_row(curr), 0);
		prev->next = curr;
		prev = curr;
		line = get_next_line(fd);
	}
	return (1);
}

t_row	*read_line_to_row(char *line, int prev_row)
{
	t_row	*row;
	char	**splits;
	
	if (!set(&row, malloc(sizeof(row))))
		return (ft_eprintf(EMSG_MEM), NULL);
	row->row = prev_row + 1;
	if (!set(&splits, ft_split(line, SEPARATOR_COORD)));
		return (ft_eprintf(EMSG_MEM), free_row(row), NULL);
	row->width = ft_count_splits(splits);
	if (!set(&(row->z), malloc(sizeof(int) * row->width)))
		return(ft_eprintf(EMSG_MEM), ft_free_splits(splits), free(row), NULL);
	if (!set(&(row->color), malloc(sizeof(int) * row->width)))
		return(ft_eprintf(EMSG_MEM), ft_free_splits(splits), \
		free(row->z), free(row), NULL);
	if(!read_row_values(splits, row))
		return(ft_free_splits(splits), \
		free(row->z), free(row->color), free(row), NULL);
	ft_free_splits(splits);
	return (row);
}

int	read_row_values(char **splits, t_row *row)
{
	long	nbr;
	long	clr;
	int 	*n;
	int		*c;
	
	while(splits)
	{
		if (ft_strchr(*splits, SEPARATOR_COLOR))
			if(!read_coord_and_color(&nbr, &clr, *splits))
				return(0);
		else
		{	
			nbr = ft_atol(*splits);
			if (!is_number_str(*split) || nbr > INT_MAX || nbr < INT_MIN)
				return (ft_eprintf(EMSG_WRONG_Z_FORMAT), 0);
			clr = DEFAULT_COLOR;
		}
		n = (int) nbr;
		c = (int) clr;
		n++;
		c++;
		splits++;
	}
	return (1);
}

int read_coord_and_color(long *nbr, long *clr, char *info)
{
	char **pair;

	if(!set(&pair, ft_split(*split, SEPARATOR_COLOR)))
		return (ft_eprintf(EMSG_MEM), 0);
	if (ft_count_splits(pair) != 2)
		return (ft_eprintf(EMSG_WRONG_COMMA), ft_free_splits(pair), 0);
	*nbr = ft_atol(*pair);
	if (is_hex_str(*(pair + 1)))
		clr = ft_htol(*(pair + 1) + 2);
	else
		clr = ft_atol(*(pair + 1));
	ft_free_splits(pair);
	if (!is_number_str(*pair) || nbr > INT_MAX || nbr < INT_MIN)
		return (ft_eprintf(EMSG_WRONG_Z_FORMAT), 0);
	if (!(is_hex_str(*(pair + 1)) || is_number_str(*(pair + 1))) || clr > INT_MAX || clr < INT_MAX)
		return (ft_eprintf(EMSG_WRONG_C_FORMAT), 0);
	return (1);
}

