/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstwipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:04:23 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libfm.h"

/* Recursively free list structure. Items are also freed [1/1]
(Warning: items shared between lists will be freed, alt fm_lstfree()) */
void	fm_lstwipe(t_fmlst *fmlst)
{
	t_fmlst	*_node;

	_node = fm_lsthead(fmlst);
	while (_node)
	{
		fmlst = _node;
		if (_node->has_nest)
			fm_lstwipe(_node->item);
		else if (_node->item)
			free(_node->item);
		_node = _node->next;
		free(fmlst);
	}
}


