/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:37 by baschnit          #+#    #+#             */
/*   Updated: 2024/09/21 17:10:37 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	n;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
		sign = 1 + '+' - (*(nptr++));
	n = 0;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}
