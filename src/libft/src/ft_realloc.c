/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:47:07 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/28 09:26:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old_ptr, size_t new_sizeof)
{
	void	*new_ptr;

	if (!old_ptr)
		return (ft_calloc(1, new_sizeof));
	if (!new_sizeof)
		return (old_ptr);
	new_ptr = ft_calloc(1, new_sizeof);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, old_ptr, new_sizeof);
	if (old_ptr)
		free(old_ptr);
	return (new_ptr);
}
