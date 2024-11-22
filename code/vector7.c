/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:45:15 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 20:49:20 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"
#include "debug.h"

void	v_ip_norm(t_vect *to_norm)
{
	double	length;

	length = v_len(to_norm);
	if (!length)
		return ;
	v_ip_scale(1 / length, to_norm);
}

t_vect	*v_ip_scale(double scale, t_vect *vect)
{
	size_t	i;
	double	*pos_old;

	pos_old = vect->values;
	i = 0;
	while (i < vect->size)
	{
		*pos_old = scale * *pos_old;
		pos_old++;
		i++;
	}
	return (vect);
}

double	v_triple(t_vect *a, t_vect *b, t_vect *c)
{
	t_vect	*cross;
	double	triple;

	cross = v_cross(b, c);
	triple = v_mult(a, cross);
	v_free(cross);
	return (triple);
}

int	v_screw_direction(t_vect *a, t_vect *b, t_vect *n)
{
	double	triple;

	if (v_len(a) == 0 || v_len(b) == 0)
		return (0);
	triple = v_triple(a, b, n);
	if (triple > 0)
		return (1);
	else if (triple < 0)
		return (-1);
	else
		return (0);

}

double	v_angle(t_vect *a, t_vect *b, t_vect *n)
{
	double	len_a;
	double	len_b;

	len_a = v_len(a);
	len_b = v_len(b);
	if (len_a == 0 || len_b == 0)
		return (0);
	print_vector(a, "vector a");
	print_vector(b, "vector b");
	return (-v_screw_direction(a, b, n) * acos(fmax(fmin(v_mult(a, b) / len_a / len_b, 1), -1)) / M_PI * 180);
}
