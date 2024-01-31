/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:43:17 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/08 17:02:30 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_utox(char	*str, uint64_t ui)
{
	char	hex[17];
	size_t	mod16;

	ft_strlcpy(hex, "0123456789abcdef\0", 17);
	if (ui == 0)
	{
		*str = '0';
		str++;
	}
	while (ui > 0)
	{
		mod16 = ui % 16;
		*str = hex[mod16];
		ui = ui / 16;
		str++;
	}
	ft_bzero(str, NUL_SZ);
}
