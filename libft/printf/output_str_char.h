/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_str_char.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:08:38 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:37:04 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_STR_CHAR_H
# define OUTPUT_STR_CHAR_H

int	ft_printf_putchar_n(int fd, char c, int n);
int	ft_printf_putstr(int fd, t_spec *spec, char *str);
int	ft_putstr(int fd, char *str);
int	ft_putnstr(int fd, char *str, int n);

#endif