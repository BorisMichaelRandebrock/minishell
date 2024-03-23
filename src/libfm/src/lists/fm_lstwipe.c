/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstwipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:04:23 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 14:23:06 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fm_lists.h"

//Recursively free list structure. Items are freed.
void	fm_lstwipe(t_fmlst *parent)
{
	t_fmlst	*_node;

	_node = parent;
	while (_node)
	{
		parent = _node;
		if (_node->nested)
			fm_lstwipe(_node->item);
		else
			free(_node->item);
		_node = _node->next;
		free(parent);
	}
}
