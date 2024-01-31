/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:00:21 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 12:00:13 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;
	size_t	s_length;

	i = 0;
	s_length = ft_strlen(s);
	result = ft_calloc(s_length + NUL_SZ, sizeof(char));
	if (!result)
	{
		return (NULL);
	}
	while (i < s_length)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
