/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixel.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 06:37:01 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/23 06:57:54 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_PIXEL_H
# define PRINT_PIXEL_H

# include "canvas.h"

void	print_pixel(t_canvas *img, int x, int y, int color);
void	print_pixel_aa_x_based(t_canvas *img, int x, double y, int color);
void	print_pixel_aa_y_based(t_canvas *img, double x, int y, int color);

#endif