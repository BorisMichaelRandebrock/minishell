/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rszarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:01:22 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/04 19:32:51 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char **ft_rszarray(char **src, int new_sz)
{
	char	**buffer;
	size_t	i;

	buffer = ft_calloc(new_sz, sizeof(char *));
	i = 0;
	while (src[i])
	{
		if (buffer[i])
			buffer[i] = src[i];
		i++;
	}
	buffer[i] = NULL;
	//free(src);
	return (buffer);
}

