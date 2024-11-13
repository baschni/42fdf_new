/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:45:44 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 22:50:33 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "t_spec.h"
#include "libft.h"

void	free_spec(void *vspec)
{
	t_spec	*spec;

	spec = (t_spec *) vspec;
	free(spec->str);
	free(spec);
}

void	free_specs(t_spec_list **specs)
{
	ft_lstclear((t_list **) specs, &free_spec);
}
