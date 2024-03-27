/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstprep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:27:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfm.h"

/* Create/Prepend new fmlst node with item and expection handler [1/2]
Returns new node */
t_fmlst	*fm_lstprep(t_fmlst **fmlst, void *item, t_fmexcpt ex)
{
	t_fmlst	*_node;
	t_fmlst	*_head;

	_head = fm_lsthead(*fmlst);
	_node = fm_calloc_(sizeof(t_fmlst), ex);
	if (!_node)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	_node->item = item;
	_node->has_nest = false;
	if (!*fmlst)
		*fmlst = _node;
	else
	{
		_node->next = _head;
		_head->prev = _node;
		*fmlst = _node;
	}
	return (_node);
}

/* Create/Prepend new fmlst node with item and expection handler and arg [2/2]
Returns new node */
t_fmlst	*fm_lstprep2(t_fmlst **fmlst, void *item, t_fmexcpt ex, void *ex_arg)
{
	t_fmlst	*_node;
	t_fmlst	*_head;

	_head = fm_lsthead(*fmlst);
	_node = fm_calloc_(sizeof(t_fmlst), ex);
	if (!_node)
	{
		if (!ex)
			return (NULL);
		(ex)(ex_arg);
	}
	_node->item = item;
	_node->has_nest = false;
	if (*fmlst)
		*fmlst = _node;
	else
	{
		_node->next = _head;
		_head->prev = _node;
		*fmlst = _node;
	}
	return (_node);
}
