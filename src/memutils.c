/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 17:20:28 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

//Protected allocation with calloc
void	*sh_calloc(size_t num, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(num, size);
	if (!alloc)
		sh_perror(MEM_ERROR);
	return (alloc);
}

//Protected reallocation with calloc
void	*sh_ralloc(void *old, size_t new_size)
{
	void	*ralloc;

	if (!old)
		return (sh_calloc(1, new_size));
	if (new_size == 0)
		return (old);
	ralloc = sh_calloc(1, new_size);
	ft_memcpy(ralloc, old, new_size);
	if (old)
		sh_free(&old);
	return (ralloc);
}

//Protect 3rd party allocations, optional free old
void	*sh_guard(void *alloc, void *old)
{
	if (old)
		sh_free(&old);
	if (!alloc)
		sh_perror(MEM_ERROR);
	return (alloc);
}

//Protected free from already freed pointers, pass REFERENCE to ptr (&ptr)!!
void	sh_free(void *ptr)
{
	void	**ref;

	ref = ptr;
	free(*ref);
	*ref = NULL;
}
