/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:23:36 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/17 13:58:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_SZ			1
#define IDX_OFFSET		1

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
