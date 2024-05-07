/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:23:36 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/07 16:03:05 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_SZ			1
#define FILE_FOUND		0
#define IDX_OFFSET		1
#define FILE_ERROR		-1
#define FILE_ERROR_MSG	"File error"

char	*sh_get_dir_name(char *filename)
{
	size_t	path_size;
	char	*dir_name;
	char	*end;
	int		i;

	end = NULL;
	i = 0;
	while (filename[i])
	{
		if (filename[i] == '/')
			end = &filename[i];
		i++;
	}
	if (!end)
		return (sh_guard(ft_strdup("."), NULL));
	path_size = (end - filename) + IDX_OFFSET;
	if (path_size < 1)
		path_size = 1;
	dir_name = sh_calloc(1, (path_size + NUL_SZ) * sizeof(char));
	ft_strlcpy(dir_name, filename, path_size);
	return (dir_name);
}

bool	sh_check_current_dir(char *cmd_name)
{
	if (access(cmd_name, F_OK) == SUCCESS)
	{
		if (access(cmd_name, X_OK) == SUCCESS)
			return (true);
	}
	return (false);
}

bool	sh_fexists(char *filename)
{
	if (access(filename, F_OK) != FILE_FOUND)
		return (false);
	return (true);
}

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
