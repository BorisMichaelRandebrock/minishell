/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_mshld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:09:54 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 22:44:21 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fm_memory.h"

//TODO integration with lists

//Shield allocation with exception handler [1/4]
void	*fm_mshld(void *alloc, t_excpt ex)
{
	if (!alloc)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	return (alloc);
}

//Shield allocation with exception handler and exception arg [2/4]
void	*fm_mshld2(void *alloc, t_excpt ex, void *ex_arg)
{
	if (!alloc)
	{
		if (!ex)
			return (NULL);
		(ex)(ex_arg);
	}
	return (alloc);
}

//Shield allocation with exception handler, also free ptr [3/4]
void	*fm_mshld3(void *alloc, t_excpt ex, void *free_ptr)
{
	if (free)
		free(free_ptr);
	if (!alloc)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	return (alloc);
}

//Shield allocation with exception handler and arg, also free ptr [4/4]
void	*fm_mshld4(void *alloc, t_excpt ex, void *ex_arg, void *free_ptr)
{
	if (free)
		free(free_ptr);
	if (!alloc)
	{
		if (!ex)
			return (NULL);
		(ex)(ex_arg);
	}
	return (alloc);
}
