/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 12:59:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fm_memory.h"

//Alloc heap memory, zero init. Nullable exception custom function and arg.
void	*fm_calloc_(size_t size, t_excpt nble_ex, void *nble_arg)
{
	char	*alloc;
	size_t	i;

	alloc = fm_malloc_(size, nble_ex, nble_arg);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < size)
		alloc[i++] = '\0';
	return (alloc);
}
