/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:14:52 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 14:22:18 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fm_memory.h"

//Alloc heap memory. Nullable exception custom function and arg.
void	*fm_malloc_(size_t size, t_excpt nble_ex, void *nble_arg)
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

