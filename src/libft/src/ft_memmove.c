/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:06:38 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/08 16:59:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*result;

	result = dest;
	i = 0;
	while ((dest || src) && i++ < n)
	{
		if (dest < src)
		{
			*(unsigned char *)dest++ = *(unsigned char *)src++;
		}
		else
		{
			if (i == 1)
			{
				dest += n;
				src += n;
			}
			*(unsigned char *)--dest = *(unsigned char *)--src;
		}
	}
	return (result);
}
