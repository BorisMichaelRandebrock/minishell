/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:53:57 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 12:04:30 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		return (ft_calloc(1, sizeof(char)));
	}
	if (ft_strlen(s) - start < len)
	{
		len = ft_strlen(s) - start;
	}
	sub = ft_calloc((len + NUL_SZ), sizeof(char));
	if (sub == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}
