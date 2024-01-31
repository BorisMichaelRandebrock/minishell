/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 12:43:35 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 12:02:01 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str_ptr;
	char	target_chr;

	str_ptr = (char *)s;
	target_chr = (char)c;
	while (*str_ptr)
	{
		if (*str_ptr == target_chr)
		{
			return (str_ptr);
		}
		str_ptr++;
	}
	if (target_chr == '\0')
	{
		return (str_ptr);
	}
	return (NULL);
}
