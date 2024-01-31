/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 23:38:17 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:59:50 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	count;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	dst += dst_len;
	count = dst_len;
	if (size > 0)
	{
		while (*src && count++ < (size - NUL_SZ))
		{
			*dst++ = *src++;
		}
		*dst = '\0';
		dst -= dst_len;
	}
	if (size <= dst_len)
	{
		return (src_len + size);
	}
	return (dst_len + src_len);
}
