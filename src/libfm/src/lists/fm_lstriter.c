/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstriter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:15:48 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libfm.h"

//Recursively iterate a fmlist and apply argless function to node [1/2]
void	fm_lstriter(t_fmlst **fmlst, t_fmiter fn)
{
	t_fmlst	*_node;

	if (!fmlst || !fn)
		return ;
	_node = *fmlst;
	while (_node)
	{
		if (_node->has_nest)
			fm_lstiter((t_fmlst **)&_node->item, fn);
		(fn)(_node, NULL);
		_node = _node->next;
	}
}

//Recursively iterate a fmlist and apply function with arg to node [2/2]
void	fm_lstriter2(t_fmlst **fmlst, t_fmiter fn, void *fn_arg)
{
	t_fmlst	*_node;

	if (!fmlst || !fn)
		return ;
	_node = *fmlst;
	while (_node)
	{
		if (_node->has_nest)
			fm_lstiter2((t_fmlst **)&_node->item, fn, fn_arg);
		(fn)(_node, fn_arg);
		_node = _node->next;
	}
}
