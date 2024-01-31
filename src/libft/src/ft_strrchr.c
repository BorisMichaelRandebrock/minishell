/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:03:10 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 12:03:32 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str_ptr;
	char	*last_ptr;
	char	target_chr;

	str_ptr = (char *)s;
	last_ptr = str_ptr;
	target_chr = (char)c;
	while (*str_ptr)
	{
		if (*str_ptr == target_chr)
		{
			last_ptr = str_ptr;
		}
		str_ptr++;
	}
	if (target_chr == '\0')
	{
		return (str_ptr);
	}
	if (*last_ptr == target_chr)
	{
		return (last_ptr);
	}
	return (NULL);
}
