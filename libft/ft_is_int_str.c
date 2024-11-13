/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:55:00 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 21:12:32 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_int_str(char *s)
{
	int	i;

	i = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (i == 0)
		{
			if (*s != '-' && !ft_isdigit(*s))
				return (0);
		}
		else if (!ft_isdigit(*s))
		{
			return (0);
		}
		s++;
		i++;
	}
	return (1);
}
