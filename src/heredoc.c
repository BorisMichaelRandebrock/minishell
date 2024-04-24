/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/24 14:34:18 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "readline/readline.h"
#include "minishell.h"

#define QUOTES_SZ	2
#define IDX_OFFSET	1

static	bool	_has_expansion(char *dlmt)
{
	if (*dlmt == '\'' || *dlmt == '"')
	{
		if (dlmt[ft_strlen(dlmt) - IDX_OFFSET] == *dlmt)
		{
			ft_memmove(dlmt, &dlmt[1], ft_strlen(dlmt) - QUOTES_SZ);
			dlmt[ft_strlen(dlmt) - QUOTES_SZ] = '\0';
			return (false);
		}
	}
	return (true);
}

void	invoke_heredoc(char *dlmt, int tx_wr)
{
	char	*line;
	bool	xflag;

	line = NULL;
	xflag = _has_expansion(dlmt);
	while (true)
	{
		line = readline("> ");
		if (xflag)
			input_expansion(&line);
		if (!line)
			write(STDOUT_FILENO, "\n", 1);
		if (!line || !ft_strncmp(line, dlmt, ft_strlen(dlmt)))
			break ;
		write(tx_wr, line, ft_strlen(line));
		write(tx_wr, "\n", 1);
		sh_free(&line);
	}
	sh_free(&line);
}
