/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/13 16:11:31 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include "minishell.h"

#define HERE_DOC_PROMPT "\033[1;31m> \033[0m"
#define QUOTES_SZ	2
#define IDX_OFFSET	1

static	bool _has_expansion(char *dlmt)
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

//TODO expansion
void	invoke_heredoc(char *dlmt, int to_proc_fd)
{
	char	*line;
	bool	xflag;

	line = NULL;
	xflag = _has_expansion(dlmt);
	while (true)
	{
		line = readline(HERE_DOC_PROMPT);
		if (xflag)
			input_expansion(&line);
		if (!line)
			write(STDOUT_FILENO, "\n", 1);
		if (!line || !ft_strncmp(line, dlmt, ft_strlen(dlmt)))
			break ;
		write(to_proc_fd, line, ft_strlen(line));
		write(to_proc_fd, "\n", 1);
		sh_free(&line);
	}
	sh_free(&line);
}
