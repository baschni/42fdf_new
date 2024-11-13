/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:13:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/09 21:17:52 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	auto_free_type(int type, void *ptr, t_list **mallocs_history);

/**
 * @brief set a target ptr to a newly allocated memory ptr while registering
 * both in a list
 * 
 * This is the central function of the auto free module. It receives a newly
 * allocated memory range together with a **ptr to store the address of the newly
 * allocated memory. It will store both addresses to a list passed as parameter
 * (mallocs_history) as long as the type. This list will later be used, when one
 * of the auto free functions is used, to free all the allocated memory addresses
 * and set the according parent pointers to NULL.
 * 
 * @param mallocs_history	list of structure typed_ptr containing type and two 
 * pointers
 * @param type 				integer variable holding a value of e_types which is 
 * 							to be defined individually for each application
 * @param target 			parent pointer to be set to the memory address on
 * 							allocation and to be set to NULL in auto free
 * 							function
 * @param void_new 			address returned by malloc upon allocating new memory
 * @return void* 			returns NULL if malloc failed or the address to the
 * 							allocated memory
*/

void	*fnew(t_list **mallocs_history, int type, void *vtarget, void *void_new)
{
	*mallocs_history = NULL;
	return (new(mallocs_history, type, vtarget, void_new));
}

t_list	*free_and_return_previous(t_list *list, t_list *after)
{
	while (list)
	{
		if (list->next == after)
			break ;
		list = list->next;
	}
	free(after->content);
	free(after);
	if (list)
		list->next = NULL;
	return (list);
}

void	*auto_free(t_list **mallocs_history)
{
	t_typed_ptr	*tp;
	t_list		*list_item;

	list_item = ft_lstlast(*mallocs_history);
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		if (tp->ptr_malloc)
			auto_free_type(tp->type, tp->ptr_malloc, mallocs_history);
		tp->ptr_malloc = NULL;
		*(tp->ptr_storage) = NULL;
		list_item = free_and_return_previous(*mallocs_history, list_item);
	}
	*mallocs_history = NULL;
	return (NULL);
}

void	*auto_free_but_one(t_list **mallocs_history, void *ptr_to_spare)
{
	t_typed_ptr	*tp;
	t_list		*list_item;

	list_item = ft_lstlast(*mallocs_history);
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		if (tp->ptr_malloc != ptr_to_spare)
		{
			if (tp->ptr_malloc)
				auto_free_type(tp->type, tp->ptr_malloc, mallocs_history);
			tp->ptr_malloc = NULL;
			*(tp->ptr_storage) = NULL;
		}
		list_item = free_and_return_previous(*mallocs_history, list_item);
	}
	*mallocs_history = NULL;
	return (ptr_to_spare);
}

void	*auto_free_but_two(t_list **hist, void *ptr_to_ret, void *ptr_to_spare)
{
	t_typed_ptr	*tp;
	t_list		*list_item;

	list_item = ft_lstlast(*hist);
	while (list_item)
	{
		tp = (t_typed_ptr *) list_item->content;
		if (tp->ptr_malloc != ptr_to_ret && tp->ptr_malloc != ptr_to_spare)
		{
			if (tp->ptr_malloc)
				auto_free_type(tp->type, tp->ptr_malloc, hist);
			tp->ptr_malloc = NULL;
			*(tp->ptr_storage) = NULL;
		}
		list_item = free_and_return_previous(*hist, list_item);
	}
	*hist = NULL;
	return (ptr_to_ret);
}
