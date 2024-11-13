/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_hex_int_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:59:35 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:35:36 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#include "libft.h"
#include "null_str.h"
#include "t_spec.h"
#include "output_general2.h"
#include "output_str_char.h"

static int	print_hex(int fd, uintptr_t nbr, char upper_or_lower)
{
	int		remainder;
	char	out;
	int		written;

	written = 0;
	if (nbr / 16 != 0)
	{
		remainder = print_hex(fd, nbr / 16, upper_or_lower);
		if (remainder < 0)
			return (-1);
		written += remainder;
	}
	remainder = nbr % 16;
	if (remainder < 10)
		out = '0' + remainder;
	else
		out = upper_or_lower - 'x' + 'a' + remainder - 10;
	if (write(fd, &out, 1) < 0)
		return (-1);
	return (written + 1);
}

int	ft_printf_ui_ptr(int fd, unsigned int n, char conv)
{
	if (conv == 'p')
		return (print_hex(fd, n, 'x'));
	else
		return (print_hex(fd, n, conv));
}

int	ft_printf_unsigned_int(int fd, t_spec *spec, unsigned int n)
{
	int	written;
	int	ret;

	if (n == 0 && spec->precision == 0 && \
	spec->conv != 'i' && spec->conv != 'd')
		return (0);
	written = 0;
	if (ft_strchr("uid", spec->conv))
	{
		if (n >= 10)
		{
			ret = ft_printf_unsigned_int(fd, spec, n / 10);
			if (ret < 0)
				return (-1);
			written += ret;
		}
		if (ft_printf_putchar(fd, '0' + n % 10) < 0)
			return (-1);
		written++;
	}
	else
	{
		return (ft_printf_ui_ptr(fd, n, spec->conv));
	}
	return (written);
}

int	ft_printf_pointer(int fd, t_spec *spec, void *ptr)
{
	(void) spec;
	if (!ptr)
	{
		if (__ON_LINUX)
			return (ft_putstr(fd, LINUX_OUTPUT_PTR_NULL));
		if (spec->precision != 0)
			return (print_hex(fd, 0, 'x'));
		return (0);
	}
	return (print_hex(fd, (uintptr_t) ptr, 'x'));
}

int	ft_printf_int(int fd, t_spec *spec, int n)
{
	int		written;
	int		ret;
	char	c;

	if (n == 0 && spec->precision == 0)
		return (0);
	written = 0;
	if (n / 10 != 0)
	{
		ret = ft_printf_unsigned_int(fd, spec, n / 10 * (1 - 2 * (n < 0)));
		if (ret < 0)
			return (-1);
		written = ret;
	}
	c = (n % 10) * (1 - 2 * (n < 0)) + '0';
	if (write(fd, &c, 1) < 0)
		return (-1);
	written++;
	return (written);
}
