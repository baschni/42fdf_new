/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_general2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:48:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:43:18 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#include "libft.h"
#include "null_str.h"
#include "t_spec.h"
#include "t_arg.h"
#include "output_str_char.h"

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

static char	get_sign(t_arg *arg, t_spec *spec)
{
	char	conv;
	char	sign;

	conv = spec->conv;
	sign = 0;
	if (spec->sign == '+')
		if (conv == 'd' || conv == 'i' || (conv == 'p' && arg->p && __ON_LINUX))
			sign = '+';
	if (spec->sign == ' ')
		if (conv == 'd' || conv == 'i' || (conv == 'p' && arg->p && __ON_LINUX))
			sign = ' ';
	if ((conv == 'd' || conv == 'i') && arg->i < 0)
		sign = '-';
	return (sign);
}

int	ft_printf_putchar(int fd, char c)
{
	if (write(fd, &c, 1) < 0)
		return (-1);
	return (1);
}

int	print_sign_and_prefix(int fd, int sign, int prefix, char conv)
{
	if (sign)
		if (ft_printf_putchar(fd, sign) == -1)
			return (-1);
	if (prefix && conv == 'X')
		if (ft_putstr(fd, "0X") == -1)
			return (-1);
	if (prefix && conv != 'X')
		if (ft_putstr(fd, "0x") == -1)
			return (-1);
	return (0);
}

int	print_padding(int fd, t_spec *spec, t_arg *arg, int dzero_len[2])
{
	int	delta;
	int	sign;
	int	prefix;

	sign = get_sign(arg, spec);
	prefix = (((spec->conv == 'x' || spec->conv == 'X') && spec->alternate && \
	arg->u != 0) || (spec->conv == 'p' && (arg->p != NULL || !__ON_LINUX))) * 2;
	delta = max(spec->width - dzero_len[0] - dzero_len[1] \
	- (sign != 0) - prefix, 0);
	if (spec->padding == '-')
		delta = 0;
	if (spec->padding != '0' || (!__ON_LINUX && spec->precision != -1) \
	|| (__ON_LINUX && spec->conv == 'p' && arg->p == NULL))
		if (ft_printf_putchar_n(fd, ' ', delta) == -1)
			return (-1);
	if (print_sign_and_prefix(fd, sign, prefix, spec->conv) == -1)
		return (-1);
	if (ft_printf_putchar_n(fd, spec->precision_padding, dzero_len[0]) == -1)
		return (-1);
	if (spec->padding == '0' && !(spec->conv == 'p' && arg->p == NULL && \
	__ON_LINUX) && !(!__ON_LINUX && spec->precision != -1))
		if (ft_printf_putchar_n(fd, '0', delta) == -1)
			return (-1);
	return (delta + dzero_len[0] + prefix + (sign != 0));
}
