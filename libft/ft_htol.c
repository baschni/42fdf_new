/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:08:43 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 21:12:04 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_htol(const char *nptr)
{
	long	n;

	n = 0;
	if (!nptr)
		return (0);
	while (ft_isspace(*nptr))
		nptr++;
	while (*nptr && ft_strchr("01234567890ABCDEFabcdef", *nptr))
	{
		n = n * 16;
		if (*nptr >= 'A' && *nptr <= 'F')
			n += (*nptr - 'A' + 10);
		else if (*nptr >= 'a' && *nptr <= 'f')
			n += (*nptr - 'a' + 10);
		else
			n += (*nptr - '0');
		nptr++;
	}
	return (n);
}
