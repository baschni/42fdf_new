/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_hex_int_ptr.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:08:27 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:37:11 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_HEX_INT_PTR_H
# define OUTPUT_HEX_INT_PTR_H

int	ft_printf_int(int fd, t_spec *spec, int n);
int	ft_printf_pointer(int fd, t_spec *spec, void *ptr);
int	ft_printf_unsigned_int(int fd, t_spec *spec, unsigned int n);

#endif