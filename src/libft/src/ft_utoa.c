/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:26:23 by fmontser          #+#    #+#             */
/*   Updated: 2023/03/01 12:30:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	_ucount_c(unsigned int num)
{
	size_t	count;

	count = 0;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	if (count == 0)
	{
		return (1);
	}
	return (count);
}

char	*ft_utoa(unsigned int num)
{
	char	*result;
	size_t	r_length;
	size_t	i;
	short	n_flag;

	n_flag = 1;
	r_length = _ucount_c(num);
	i = r_length;
	result = ft_calloc(r_length + 1, sizeof(char));
	if (!result)
		return (0);
	while (i-- > 0)
	{
		result[r_length - 1] = ((num % 10) * n_flag) + '0';
		num /= 10;
		r_length--;
	}
	return (result);
}
