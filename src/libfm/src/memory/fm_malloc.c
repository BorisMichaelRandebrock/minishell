/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 21:46:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fm_memory.h"
#include "fm_lists.h"

//Alloc heap memory, with exception handler [1/5]
void	*fm_malloc_(size_t size, t_excpt ex)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		if (!ex)
			return (NULL);
		(ex)(NULL);
	}
	return (alloc);
}

//Alloc heap memory, optional ex handler and arg [2/5]
void	*fm_malloc2_(size_t size, t_excpt ex, void *ex_arg)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		if (!ex)
			return (NULL);
		(ex)(ex_arg);
	}
	return (alloc);
}

//Alloc heap memory, with exception handler and lst append/create [3/5]
void	*fm_malloc3_(size_t size, t_excpt ex, t_fmlst *applst)
{
	void	*alloc;

	alloc = fm_malloc(size, ex);
	//TODO append lst
	return (alloc);
}

//Alloc heap memory, with exception handler and lst prepend/create [4/5]
void	*fm_malloc4_(size_t size, t_excpt ex, t_fmlst *preplst)
{
	void	*alloc;

	alloc = fm_malloc(size, ex);
	//TODO prepend to list
	return (alloc);
}

//Alloc heap memory, with exception handler and lst nest/create [5/5]
void	*fm_malloc5_(size_t size, t_excpt ex, t_fmlst *nestlst)
{
	void	*alloc;

	alloc = fm_malloc(size, ex);
	//TODO nest list
	return (alloc);
}
