/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:02:47 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 21:08:43 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

t_rlst	*newline_in_list(t_rlst *rest)
{
	if (!rest)
		return (NULL);
	if (ft_strchr(rest->content, '\n'))
		return (rest);
	while (rest->next)
	{
		rest = rest->next;
		if (ft_strchr(rest->content, '\n'))
			return (rest);
	}
	return (NULL);
}

char	*add_string_to_back_of_list(t_rlst **rest, char *str)
{
	t_rlst	*new;
	t_rlst	*old;
	char	*new_str;

	new = malloc(sizeof(t_rlst));
	if (!new)
		return (ft_lstclear((t_list **) rest, free), NULL);
	new_str = ft_strdup(str);
	if (!new_str)
	{
		free(new);
		return (ft_lstclear((t_list **) rest, free), NULL);
	}
	new->content = new_str;
	new->next = (NULL);
	if (!*rest)
	{
		*rest = new;
		return (new_str);
	}
	old = *rest;
	while (old->next)
		old = old->next;
	old->next = new;
	return (new_str);
}

char	*manage_rest_and_return_newline(t_rlst **rest, char *left_over)
{
	t_rlst	*split;
	char	*s;

	split = newline_in_list(*rest);
	s = ft_strchr(split->content, '\n') + 1;
	ft_stpcpy(left_over, s);
	*s = '\0';
	s = join_list_to_str(*rest);
	ft_lstclear((t_list **) rest, free);
	*rest = (NULL);
	return (s);
}

char	*read_to_buffer(int fd, t_rlst **rest, char *buffer, char *left_over)
{
	char	*result;
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!add_string_to_back_of_list(rest, buffer))
			return (ft_lstclear((t_list **) rest, free), NULL);
		if (ft_strchr(buffer, '\n'))
			return (manage_rest_and_return_newline(rest, left_over));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (ft_lstclear((t_list **) rest, free), NULL);
	result = join_list_to_str(*rest);
	ft_lstclear((t_list **) rest, free);
	if (!result)
		return (NULL);
	if (ft_strlen(result) != 0)
		return (result);
	free(result);
	return (NULL);
}

/**
 * @brief Return next line of file descriptor (param fd) The function is a
 * wrapper to the library function read, with a central static variable rest,
 * which will buffer the contents of read until a new line character is found or
 *  for the read contents after a newline character.
 *
 * The function will first check for a valid file descriptor and will free the
 * static variable rest, if fd is not valid. Otherwise it will check the rest
 * for a newline character, in which case it will construct a newline of all
 * string bits until this newline and reduce the rest accordingly. If not, it
 * will allocate a buffer and launch the function read_to_buffer to read into it
 *  until a newline is read, the end of the file is reached or an error occurs.
 *
 * @param 	fd		File descriptor to the file or stdin to read from.
 *
 * @var		rest	stores the rest after a \n in between function calls
 * @var		buffer	buffer string as large as BUFFER_SIZE + 1
 * @var		result	return value of function read_to_buffer
 *
 * @return 	char* 	returns every character until the next \n in the fd.
*/
char	*get_next_line(int fd)
{
	static char	left_over[BUFFER_SIZE + 1];
	t_rlst		*no_newline;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	no_newline = (NULL);
	if (!add_string_to_back_of_list(&no_newline, left_over))
		return (NULL);
	left_over[0] = '\0';
	if (newline_in_list(no_newline))
		return (manage_rest_and_return_newline(&no_newline, left_over));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		if (no_newline)
			return (ft_lstclear((t_list **) &no_newline, free), NULL);
		return (NULL);
	}
	result = read_to_buffer(fd, &no_newline, buffer, left_over);
	free(buffer);
	return (result);
}
