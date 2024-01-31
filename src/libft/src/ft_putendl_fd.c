/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:18:06 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 11:25:10 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	s_length;
	char	nl;

	nl = '\n';
	s_length = ft_strlen(s);
	write(fd, s, s_length);
	write(fd, &nl, sizeof(char));
}
