/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:23:36 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/07 16:28:05 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

#define FILE_NOT_FOUND	-1
#define FILE_NOT_EXEC	-1

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
