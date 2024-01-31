/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:10:07 by fmontser          #+#    #+#             */
/*   Updated: 2023/11/18 23:03:31 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

// ALLOCATES MEMORY!

void	*ft_fload(char *file_path, int file_size)
{
	void	*fptr;
	int		fd;

	fptr = ft_calloc(sizeof(char), file_size);
	if (!fptr)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	while (read(fd, fptr, sizeof(char)) != READ_EOF)
	{
		fptr++;
	}
	close(fd);
	return (fptr - file_size);
}
