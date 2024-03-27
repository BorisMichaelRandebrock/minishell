/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstxtrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:52:17 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libfm.h"

/*Extract a node from its fmlst.
Return pointer to extracted node*/
t_fmlst	*fm_lstxtrc(t_fmlst **node)
{
	t_fmlst	*_node;

	if (!node || !*node)
		return (NULL);
	_node = *node;
	if (!_node->prev)
	{
		if (_node->next)
		{
			_node->next->prev = NULL;
			*node = _node->next;
		}
	}
	else if (_node->next)
	{
		_node->prev->next = _node->next;
		_node->next->prev = _node->prev;
	}
	_node->next = NULL;
	_node->prev = NULL;
	return (_node);
}

/*Extract a node from its nested fmlst given its parent fmlst.
Return pointer to extracted node*/
t_fmlst	*fm_lstxtrc2(t_fmlst **node, t_fmlst *parent)
{
	t_fmlst	*_node;

	if (!node || !*node || !parent)
		return (NULL);
	_node = *node;
	if (!_node->prev)
	{
		parent = fm_lstfind(parent, _node);
		if (_node->next)
		{
			_node->next->prev = NULL;
			*node = _node->next;
			parent->item = *node;
		}
		else
			parent->item = NULL;
	}
	else if (_node->next)
	{
		_node->prev->next = _node->next;
		_node->next->prev = _node->prev;
	}
	_node->next = NULL;
	_node->prev = NULL;
	return (_node);
}

