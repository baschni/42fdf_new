/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:45:15 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/22 13:33:35 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"

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

double v_triple(t_vect *a, t_vect *b, t_vect *c)
{
	t_vect *cross;
	double triple;

	cross = v_cross(b, c);
	triple = v_mult(a, cross);
	v_free(cross);
	return (triple);	
}

int v_screw_direction(t_vect *a, t_vect *b)
{

	t_vect *temp;
	double triple;
	

	if(v_len(a) == 0 || v_len(b) == 0)
		return (0);
	temp = v_cross_normed(a, b);
	triple = v_triple(a, b, temp);
	v_free(temp);
	if (triple > 0)
		return (1);
	else if (triple < 0)
		return (-1);
	else
		return (0);
	
}

double	v_angle(t_vect *a, t_vect *b)
{
	double len_a;
	double len_b;

	len_a = v_len(a);
	len_b = v_len(b);
	if (len_a == 0 || len_b == 0)
		return (0);
	return v_screw_direction(a, b) * acos(v_mult(a, b) / len_a / len_b);
}



// int	v_turn_vect_x(t_vect *y, t_vect *axes, double angle)
// {
		
// 	double	cosv;
// 	double	sinv;
// 	t_vect *temp;
// 	t_vect *temp2;

// 	cosv = cos(angle * M_PI / 180);
// 	sinv = sin(angle * M_PI / 180);
// 	temp = v_cross_normed(y, axes);
// 	temp2 = v_norm(y);
	
	
// }