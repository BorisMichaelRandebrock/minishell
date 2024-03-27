/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 10:28:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libfm.h"

//Iterate a fmlist and apply argless function to node [1/2]
void	fm_lstiter(t_fmlst **fmlst, t_fmiter fn)
{
	t_fmlst	*_node;

	if (!fmlst || !fn)
		return ;
	_node = *fmlst;
	while (_node)
	{
		(fn)(_node, NULL);
		_node = _node->next;
	}
}

//Iterate a fmlist and apply function with arg to node [2/2]
void	fm_lstiter2(t_fmlst **fmlst, t_fmiter fn, void *fn_arg)
{
	t_fmlst	*_node;

	if (!fmlst || !fn)
		return ;
	_node = *fmlst;
	while (_node)
	{
		(fn)(_node, fn_arg);
		_node = _node->next;
	}
}
