/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:29:29 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/08 16:59:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	_count_d(int n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
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

static int	_manage_excl(int n, int fd)
{
	if (n == 0 || n == -2147483648)
	{
		if (n == 0)
			ft_putchar_fd('0', fd);
		else
			ft_putstr_fd("-2147483648", fd);
		return (1);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	un[11];
	size_t	d_count;
	short	n_flag;

	n_flag = 1;
	d_count = _count_d(n);
	if (_manage_excl(n, fd))
	{
		return ;
	}
	if (n < 0)
	{
		n_flag *= -1;
		d_count++;
	}
	un[d_count] = '\0';
	while (n != 0)
	{
		un[--d_count] = ((n % 10) * n_flag) + '0';
		n /= 10;
	}
	if (n_flag < 0)
		un[--d_count] = '-';
	ft_putstr_fd(un, fd);
}
