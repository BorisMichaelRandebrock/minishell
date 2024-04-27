/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:23:36 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 16:08:39 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "minishell.h"

#define NUL_SZ 		1
#define FILE_FOUND	0

/* char	*sh_get_dir(char *filename)
{
	size_t	path_size;
	char	buffer[NAME_MAX];
	
} */

bool	sh_fexists(char *filename)
{
	if (access(filename, F_OK) != FILE_FOUND)
		return (false);
	return (true);
}

//TODO excepcion file
void	sh_fprelay(char *filename, int pipe_wr)
{
	int		fd;
	ssize_t	consumed;
	char	buffer[BUF_1KB + NUL_SZ];

	fd = open(filename, O_RDONLY, 0777);
	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	consumed = 1;
	while (consumed > 0)
	{
		consumed = read(fd, buffer, BUF_1KB);
		if (consumed > 0)
			write(pipe_wr, buffer, consumed);
	}
}
//TODO excepcion read
void	sh_pprelay(int pipe_rd, int pipe_wr)
{
	ssize_t	consumed;
	char	buffer[BUF_1KB + NUL_SZ];

	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	consumed = 1;
	while (consumed > 0)
	{
		consumed = read(pipe_rd, buffer, BUF_1KB);
		if (consumed > 0)
			write(pipe_wr, buffer, consumed);
	}
}
