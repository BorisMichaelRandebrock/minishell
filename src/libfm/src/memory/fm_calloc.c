/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 21:43:36 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_lists.h"
#include "fm_memory.h"

//Alloc heap memory zero it, with exception handler [1/5]
void	*fm_calloc_(size_t size, t_excpt ex)
{
	char	*alloc;
	size_t	i;

	alloc = fm_malloc_(size, ex);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}

//Alloc heap memory zero it, with exception handler [2/5] [2/5]
void	*fm_calloc2_(size_t size, t_excpt ex, void *ex_arg)
{
	char	*alloc;
	size_t	i;

	alloc = fm_malloc2_(size, ex, ex_arg);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}

//Alloc heap memory zero it, with exception handler and lst append/create [3/5]
void	*fm_calloc3_(size_t size, t_excpt ex, t_fmlst *applst)
{
	char	*alloc;
	size_t	i;

	alloc = fm_malloc3_(size, ex, applst);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}

//Alloc heap memory zero it, with exception handler and lst prepend/create [4/5]
void	*fm_calloc4_(size_t size, t_excpt ex, t_fmlst *preplst)
{
	char	*alloc;
	size_t	i;

	alloc = fm_malloc4_(size, ex, preplst);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}

//Alloc heap memory zero it, with exception handler and lst nest/create [5/5]
void	*fm_calloc5_(size_t size, t_excpt ex, t_fmlst *nestlst)
{
	char	*alloc;
	size_t	i;

	alloc = fm_malloc5_(size, ex, nestlst);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}
