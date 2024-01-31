/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:55:16 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:59:25 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + NUL_SZ, sizeof(char));
	if (result == NULL)
	{
		return (NULL);
	}
	while (*s1)
	{
		result[i++] = *s1++;
	}
	while (*s2)
	{
		result[i++] = *s2++;
	}
	return (result);
}
