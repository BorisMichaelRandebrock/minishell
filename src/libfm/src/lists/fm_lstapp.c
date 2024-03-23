/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:27:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 21:12:26 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_memory.h"
#include "fm_lists.h"


//New fmslst append/create. Returns new node pointer [1/3]
t_fmlst	*fm_lstnew_(void *item, t_fmlst *nble_fmlst)
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
	else if (opt == O_APP)
	{
		fm_lstlast(nble_fmlst)->next = new_lst;
		new_lst->prev = fm_lstlast(nble_fmlst);
	}
	else if (opt == O_PREP)
	{
		fm_lstlast(nble_fmlst)->prev = new_lst;
		new_lst->next = fm_lstlast(nble_fmlst);
	}
	return (new_lst);
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
	else if (opt == O_APP)
	{
		fm_lstlast(nble_fmlst)->next = new_lst;
		new_lst->prev = fm_lstlast(nble_fmlst);
	}
	else if (opt == O_PREP)
	{
		fm_lstlast(nble_fmlst)->prev = new_lst;
		new_lst->next = fm_lstlast(nble_fmlst);
	}
	return (new_lst);
}
