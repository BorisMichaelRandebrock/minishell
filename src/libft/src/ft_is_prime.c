/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:05:26 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:52:27 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define FIRST_PRIME 2

bool	ft_is_prime(int n)
{
	int	i;

	i = FIRST_PRIME;
	while (i < n)
	{
		if (n % i == 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}
