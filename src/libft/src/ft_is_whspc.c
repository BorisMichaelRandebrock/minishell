/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whspc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:11:21 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/18 11:38:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_whspc(char c)
{
	size_t	i;
	char	white[7];

	i = 0;
	white[0] = ' ';
	white[1] = '\t';
	white[2] = '\n';
	white[3] = '\r';
	white[4] = '\f';
	white[5] = '\v';
	white[6] = '\0';
	while (white[i])
	{
		if (c == white[i])
			return (true);
		i++;
	}
	return (false);
}
