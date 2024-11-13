/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 06:26:04 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/13 16:43:08 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	*set(void *vtarget, void *void_new)
{
	void	**target;

	target = (void **) vtarget;
	*target = void_new;
	return (void_new);
}
