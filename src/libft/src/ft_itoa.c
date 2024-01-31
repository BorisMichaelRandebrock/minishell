/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:11:13 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/08 16:59:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	_count_c(int n)
{
	size_t	count;

	count = 0;
	if (n == -2147483648)
	{
		return (11);
	}
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	if (count == 0)
	{
		return (1);
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	r_length;
	size_t	i;
	short	n_flag;

	n_flag = 1;
	r_length = _count_c(n);
	i = r_length;
	result = ft_calloc(r_length + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		i--;
		n_flag *= -1;
	}
	while (i-- > 0)
	{
		result[r_length - 1] = ((n % 10) * n_flag) + '0';
		n /= 10;
		r_length--;
	}
	return (result);
}
