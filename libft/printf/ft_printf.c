/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:59:33 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/12 14:29:31 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "libft.h"
#include "t_spec.h"
#include "free_spec.h"
#include "parse_format_str.h"
#include "split_format_str.h"
#include "output_general.h"

int	write_output(int fd, t_spec_list *specs, va_list args)
{
	int	written_bytes;
	int	total_written_bytes;

	total_written_bytes = 0;
	while (1)
	{
		written_bytes = output_conversions(fd, specs->content, args);
		if (written_bytes == -1)
			return (-1);
		total_written_bytes += written_bytes;
		if (!specs->next)
			break ;
		else
			specs = specs->next;
	}
	return (total_written_bytes);
}

/**
 * @brief will print any of the arguments in a format specified by the first
 * argument
 *
 * 1. get_specs_str_from_format_str: will split the format string into a list of
 *  specifications (each spec connected to one of the arguments or to a literal
 * that will be written out unmodified) and parse them to a t_spec type
 * structure
 * 2.
 *
 * @param format string with printf-like formatting
 * @param ... variable length list of variable type arguments to print
 * (each argument must be addressed in the format string)
 * @return int will return the number of chars written to STDOUT
*/
int	ft_vdprintf(int fd, const char *format, va_list args)
{
	t_spec_list	*specs;
	int			written_bytes;

	if (!*format)
		return (0);
	specs = NULL;
	if (!get_specs_str_from_format_str(format, &specs))
		return (-1);
	ft_lstiter((t_list *) specs, &parse_spec);
	written_bytes = write_output(fd, specs, args);
	free_specs(&specs);
	return (written_bytes);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vdprintf(STDOUT_FILENO, format, args);
	va_end(args);
	return (ret);
}

int	ft_eprintf(const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	return (ret);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vdprintf(fd, format, args);
	va_end(args);
	return (ret);
}
