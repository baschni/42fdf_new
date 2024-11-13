/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_hex_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:54:56 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 21:12:40 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_hex_str(char *s)
{
	int	i;

	i = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (i == 0)
			if (*s != '0')
				return (0);
		if (i == 1)
			if (*s != 'x')
				return (0);
		if (i > 1 && !ft_strchr("0123456789ABCDEFabcdef", *s))
			return (0);
		s++;
		i++;
	}
	return (1);
}
