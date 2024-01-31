/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:33:25 by fmontser          #+#    #+#             */
/*   Updated: 2023/03/01 13:35:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char	*str)
{
	size_t	str_length;
	char	buffer;
	size_t	i;
	size_t	j;

	str_length = ft_strlen(str);
	i = 0;
	j = str_length - 1;
	while (i < str_length / 2)
	{
		buffer = str[i];
		str[i] = str[j];
		str[j] = buffer;
		i++;
		j--;
	}
}
