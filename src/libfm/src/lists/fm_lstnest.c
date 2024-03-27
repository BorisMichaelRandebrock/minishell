/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_lstnest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:27:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:20:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfm.h"

//Create/Append and nest fmlst node and expection handler [1/2]
t_fmlst	*fm_lstnest(t_fmlst **fmlst, void *item, t_fmexcpt ex)
{
	t_fmlst	*_node;

	_node = fm_calloc_(sizeof(t_fmlst), ex);
	if (!_node)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	_node->item = item;
	_node->has_nest = false;
	fm_lstapp(fmlst, _node, ex)->has_nest = true;
	return (_node);
}

//Create/Append and nest fmlst node and expection handler and arg [2/2]
t_fmlst	*fm_lstnest2(t_fmlst **fmlst, void *item, t_fmexcpt ex, void *ex_arg)
{
	t_fmlst	*_node;

	_node = fm_calloc2_(sizeof(t_fmlst), ex, ex_arg);
	if (!_node)
	{
		if (!ex)
			return (NULL);
		(ex)(ex_arg);
	}
	_node->item = item;
	_node->has_nest = true;
	fm_lstapp2(fmlst, _node, ex, ex_arg)->has_nest = true;
	return (_node);
}
