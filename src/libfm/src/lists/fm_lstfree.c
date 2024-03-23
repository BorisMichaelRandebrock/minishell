/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:07:50 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 14:04:10 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fm_lists.h"

//Recursively free list structure. Items remain (for shared contents lists).
void	fm_lstfree(t_fmlst *parent)
{
	t_fmlst	*_node;

	_node = parent;
	while (_node)
	{
		parent = _node;
		if (_node->nested)
			fm_lstfree(_node->item);
		_node = _node->next;
		free(parent);
	}
}
