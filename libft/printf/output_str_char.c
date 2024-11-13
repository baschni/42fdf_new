/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_str_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:13:32 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:36:33 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "null_str.h"
#include "t_spec.h"

int	ft_printf_putchar_n(int fd, char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (write(fd, &c, 1) < 0)
			return (-1);
		i++;
	}
	return (n);
}

int	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (write(fd, str, 1) < 0)
			return (-1);
		i++;
		str++;
	}
	return (i);
}

int	ft_putnstr(int fd, char *str, int n)
{
	int	i;

	if (!str)
		return (ft_putstr(fd, LINUX_OUTPUT_STR_NULL));
	i = 0;
	while (*str && i < n)
	{
		if (write(fd, str, 1) < 0)
			return (-1);
		i++;
		str++;
	}
	return (i);
}

int	ft_printf_putnstr_inner(int fd, t_spec *spec, char *str)
{
	if (!str)
		str = OSX_OUTPUT_STR_NULL;
	if (spec->precision >= 0 && ((int) ft_strlen(str) > spec->precision))
		return (ft_putnstr(fd, str, spec->precision));
	else
		return (ft_putstr(fd, str));
}

int	ft_printf_putstr(int fd, t_spec *spec, char *str)
{
	int	len;
	int	ret;

	len = 0;
	if (!str && __ON_LINUX)
	{
		if (spec->precision >= 0 \
		&& (int) ft_strlen(LINUX_OUTPUT_STR_NULL) > spec->precision)
			ret = 0;
		else
		{
			ret = ft_putstr(fd, LINUX_OUTPUT_STR_NULL);
			if (ret < 0)
				return (-1);
		}
		len += ret;
	}
	else
	{
		ret = ft_printf_putnstr_inner(fd, spec, str);
		if (ret < 0)
			return (-1);
		len += ret;
	}
	return (len);
}
