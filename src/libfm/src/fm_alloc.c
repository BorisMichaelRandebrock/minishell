/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/22 15:10:18 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_alloc.h"

//Alloc heap memory. Nullable exception custom function and arg.
void	*fm_alloc_(size_t size, t_excpt nble_ex, void *nble_arg)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		if (!nble_ex)
			return (NULL);
		(nble_ex)(nble_arg);
	}
	return (alloc);
}

//Alloc heap memory, zero init. Nullable exception custom function and arg.
void	*fm_calloc_(size_t size, t_excpt nble_ex, void *nble_arg)
{
	char	*alloc;
	size_t	i;

	alloc = fm_alloc_(size, nble_ex, nble_arg);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}

//Realloc heap memory. Nullable exception custom function and arg.
void	*fm_realloc_(void *alloc, size_t size, t_excpt nble_ex, void *nble_arg)
{
	char	*_realloc;
	char	*src;
	size_t	i;

	_realloc = fm_calloc_(size, nble_ex, nble_arg);
	if (!_realloc)
		return (NULL);
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
