/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:23:36 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/15 18:12:24 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

#define NUL_SZ 1
#define FILE_NOT_FOUND	-1
#define FILE_NOT_EXEC	-1

//TODO revisar si aun es necesario alguno

bool	sh_fexists(char *filename)
{
	if (access(filename, F_OK) == FILE_NOT_FOUND)
		return (false);
	return (true);
}

bool	sh_fisexec(char *filename)
{
	if (access(filename, X_OK) == FILE_NOT_EXEC)
		return (false);
	return (true);
}

bool	sh_finpath(char *filename)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1KB + NUL_SZ];

	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i])
	{
		ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, splitted[i], BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, "/", BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, filename, BUF_1KB + NUL_SZ);
		if (access(buffer, F_OK) != FILE_NOT_FOUND)
			return (true);
		i++;
	}
	return (false);
}

//TODO excepcion file
void	sh_fpstream(char *filename, int pipe_wr)
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
		write(pipe_wr, buffer, consumed);
	}
	close(fd);
}

void	sh_ppstream(int pipe_rd, int pipe_wr)
{
	ssize_t	consumed;
	char	buffer[BUF_1KB + NUL_SZ];

	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	consumed = 1;
	while (consumed > 0)
	{
		consumed = read(pipe_rd, buffer, BUF_1KB);
		write(pipe_wr, buffer, consumed);
	}
}
