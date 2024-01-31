/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 23:56:22 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/08 16:59:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_cmp_result(const char *s1, const char *s2);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 1;
	if (n == 0)
	{
		return (0);
	}
	while (*s1 && (*s1 == *s2))
	{
		if (count >= n)
		{
			return (_cmp_result(s1, s2));
		}
		s1++;
		s2++;
		count++;
	}
	return (_cmp_result(s1, s2));
}

static int	_cmp_result(const char *s1, const char *s2)
{
	unsigned char	*str1_ptr;
	unsigned char	*str2_ptr;

	str1_ptr = (unsigned char *) s1;
	str2_ptr = (unsigned char *) s2;
	return (*str1_ptr - *str2_ptr);
}
