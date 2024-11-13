/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 06:26:04 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 21:53:22 by baschnit         ###   ########.fr       */
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

void	*new(t_list **mallocs_history, int type, void *vtarget, void *void_new)
{
	t_typed_ptr	*tp_new;
	t_list		*l_new;
	void		**target;

	target = (void **) vtarget;
	*target = NULL;
	tp_new = malloc(sizeof(t_typed_ptr));
	if (!tp_new)
		return (auto_free(mallocs_history));
	tp_new->ptr_storage = target;
	tp_new->ptr_malloc = void_new;
	tp_new->type = type;
	l_new = ft_lstnew(tp_new);
	if (!l_new)
	{
		free(tp_new);
		return (auto_free(mallocs_history));
	}
	ft_lstadd_back(mallocs_history, l_new);
	*target = void_new;
	return (void_new);
}

void	*free_list_leave_contents(t_list **mallocs_history)
{
	t_list	*iterator;
	t_list	*iterator_previous;

	iterator = *mallocs_history;
	while (iterator)
	{
		iterator_previous = iterator;
		iterator = iterator->next;
		free(iterator_previous->content);
		free(iterator_previous);
	}
	*mallocs_history = NULL;
	return (NULL);
}
