/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:02:13 by fmontser
  #+#    #+#             */
/*   Updated: 2024/03/24 10:20:56 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libfm.h"

/* Find a item in a given list. Returns node/NULL [1/2]
Returns first match found node or NULL */
t_fmlst	*fm_lstfind(t_fmlst *fmlst, void *item)
{
	t_fmlst	*_head;

	_head = fm_lsthead(fmlst);
	while (_head)
	{
		if (item == _head->item)
			return (_head);
		_head = _head->next;
	}
	return (NULL);
}

/* Find a item in a given list recursively [2/2]
Returns first match found node or NULL */
t_fmlst	*fm_lstfind2(t_fmlst *fmlst, void *item)
{
	t_fmlst	*_head;

	_head = fm_lsthead(fmlst);
	while (_head)
	{
		if (_head->has_nest)
			fm_lstfind2(_head, item);
		if (item == _head->item)
			return (_head);
		_head = _head->next;
	}
	return (NULL);
}
