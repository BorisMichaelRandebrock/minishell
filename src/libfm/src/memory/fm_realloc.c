/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 14:22:50 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fm_memory.h"

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

