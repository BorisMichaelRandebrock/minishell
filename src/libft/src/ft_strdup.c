/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:45:42 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:59:04 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	s_length;

	s_length = (size_t) ft_strlen(s) + NUL_SZ;
	duplicate = (char *)malloc(s_length);
	if (duplicate == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(duplicate, s, s_length);
	return (duplicate);
}
