/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:29:11 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/27 15:31:42 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

char	*cut_line(char *resto)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (resto[i] && resto[i] != '\n')
		i++;
	if (!resto[i])
		return (NULL);
	res = sh_calloc(1, ft_strlen(resto) - i + 1);
	i++;
	while (resto[i])
		res[j++] = resto[i++];
	res[j] = '\0';
	return (res);
}

char	*get_line(char *resto)
{
	char	*res;
	int		i;

	i = 0;
	while (resto[i] && resto[i] != '\n')
		i++;
	if (resto[i] == '\n')
		i++;
	res = sh_calloc(1, i + 1);
	i = 0;
	while (resto[i] && resto[i] != '\n')
	{
		res[i] = resto[i];
		i++;
	}
	if (resto[i] == '\n')
	{
		res[i] = '\n';
		res[i + 1] = '\0';
		return (res);
	}
	else
		res[i] = '\0';
	return (res);
}

int	is_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int _fd)
{
	static char	*resto = NULL;
	char		buffer[BUFF_1KB + 1];
	char		*line;
	int			rd;

	line = NULL;
	rd = 1;
	while (!is_line(buffer) && rd != 0)
	{
		rd = read(_fd, buffer, BUFF_1KB);
		if (rd < 0)
		{
			if (resto)
				resto = NULL;
			return (NULL);
		}
		buffer[rd] = '\0';
		resto = sh_addfree(ft_strjoin(resto, buffer));
	}
	line = get_line(resto);
	resto = cut_line(resto);
	if (!line || line[0] == '\0')
		return (NULL);
	return (line);
}
