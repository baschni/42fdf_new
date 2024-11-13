/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_list_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:13:34 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 19:10:55 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*join_list_to_str(t_rlst *start)
{
	size_t	length;
	t_rlst	*i;
	char	*str;

	if (!start)
		return (ft_strdup(""));
	i = start;
	length = ft_strlen(start->content);
	while (i->next)
	{
		i = i->next;
		length += ft_strlen(i->content);
	}
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	i = start;
	str = ft_stpcpy(str, i->content);
	while (i->next)
	{
		i = i->next;
		str = ft_stpcpy(str, i->content);
	}
	return (str - length);
}
