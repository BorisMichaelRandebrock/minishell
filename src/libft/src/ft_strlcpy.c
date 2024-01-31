/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:20:41 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:59:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	src_len = ft_strlen(src);
	if (size > 0)
	{
		while (*src && dst_len < (size - NUL_SZ))
		{
			*dst = *src;
			dst_len++;
			dst++;
			src++;
		}
		*dst = '\0';
	}
	return (src_len);
}
