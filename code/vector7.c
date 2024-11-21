/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:45:15 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 23:36:12 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// int	v_ip_turn_two_vect(t_vect *a, t_vect *b, double angle)
// {
// }