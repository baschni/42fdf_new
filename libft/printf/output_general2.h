/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_general2.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:08:07 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:49:27 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_GENERAL2_H
# define OUTPUT_GENERAL2_H

# include <stdint.h>

# include "t_arg.h"
# include "t_spec.h"

int	max(int a, int b);
int	ft_printf_putchar(int fd, char c);
int	print_padding(int fd, t_spec *spec, t_arg *arg, int dzero[2]);

#endif