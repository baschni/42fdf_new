/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_general.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:38:39 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:37:22 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_GENERAL_H
# define OUTPUT_GENERAL_H

# include <stdarg.h>
# include "t_spec.h"

int	output_conversions(int fd, t_spec *spec, va_list args);

#endif