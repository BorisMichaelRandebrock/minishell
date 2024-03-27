/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 14:09:50 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libfm.h"

//Realloc heap memory, optional ex handler [1/3]
void	*fm_realloc_(size_t size, void *alloc, t_fmexcpt ex)
{
	char	*_realloc;
	char	*src;
	size_t	i;

	if (!alloc)
		(ex)(NULL);
	_realloc = fm_calloc_(size, ex);
	src = (char *)alloc;
	i = 0;
	while (i < size && src[i])
	{
		_realloc[i] = src[i];
		i++;
	}
	alloc = _realloc;
	free(alloc);
	return (_realloc);
}

//Realloc heap memory, optional ex handler and arg [2/3]
void	*fm_realloc2_(size_t size, void *alloc, t_fmexcpt ex, void *ex_arg)
{
	char	*_realloc;
	char	*src;
	size_t	i;

	if (!alloc)
		(ex)(NULL);
	_realloc = fm_calloc2_(size, ex, ex_arg);
	src = (char *)alloc;
	i = 0;
	while (i < size && src[i])
	{
		_realloc[i] = src[i];
		i++;
	}
	alloc = _realloc;
	free(alloc);
	return (_realloc);
}

/* Realloc heap memory of list first item match, exception handler [3/3]
(Do not use for shared items) */
void	*fm_realloc3_(size_t size, void *alloc, t_fmexcpt ex, t_fmlst **fmlst)
{
	char	*_realloc;
	size_t	i;

	if (!alloc)
		(ex)(NULL);
	_realloc = fm_calloc_(size, ex);
	i = 0;
	while (i < size && ((char *)alloc)[i])
	{
		_realloc[i] = ((char *)alloc)[i];
		i++;
	}
	fm_lstfind(*fmlst, alloc)->item = _realloc;
	free(alloc);
	return (_realloc);
}

