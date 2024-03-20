/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:44:54 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/20 17:49:10 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	value;
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	value = len;
	if (len > ft_strlen(haystack))
		value = ft_strlen(haystack);
	while ((i + ft_strlen(needle)) <= value)
	{
		c = 0;
		while (haystack[i + c] == needle[c] && needle[c])
			c++;
		if (!needle[c] && haystack[i + c -1] == needle[c -1])
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}

/* char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big || *big == '\0')
		return (NULL);
	if (!little || *little == '\0' )
	{
		return ((char *)big);
	}
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len)
		{
			if (little[j + 1] == '\0')
			{
				return ((char *)big + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
} */
