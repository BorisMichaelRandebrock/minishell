/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:27:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/22 22:30:56 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_alloc.h"
#include "fm_list.h"

//Returns pointer to last node of a list given any node of it.
t_fmlst	*fm_lstlast(t_fmlst *node)
{
	t_fmlst	*last;

	last = node;
	while (last->next)
		last = last->next;
	return (last);
}

//Returns pointer to head node of a list given any node of it.
t_fmlst	*fm_lsthead(t_fmlst *node)
{
	t_fmlst	*head;

	head = node;
	while (head->prev)
		head = head->prev;
	return (head);
}

//New list node. Optional nest, append or prepend. Returns new node pointer.
t_fmlst	*fm_lstnew_(void *item, t_fmlst *nble_fmlst, t_fmlopt opt)
{
	t_fmlst	*new_lst;

	new_lst = fm_calloc_(sizeof(t_fmlst), NULL, NULL);
	if (!new_lst)
		return (NULL);
	new_lst->item = item;
	if (!nble_fmlst)
		return (new_lst);
	if (opt == O_NEST)
	{
		nble_fmlst->nested = true;
		nble_fmlst->item = new_lst;
	}
	else if (opt == O_APPEND)
	{
		fm_lstlast(nble_fmlst)->next = new_lst;
		new_lst->prev = fm_lstlast(nble_fmlst);
	}
	else if (opt == O_PREPEND)
	{
		fm_lstlast(nble_fmlst)->prev = new_lst;
		new_lst->next = fm_lstlast(nble_fmlst);
	}
	return (new_lst);
}
