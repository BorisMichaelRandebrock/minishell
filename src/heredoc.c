/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/11 12:18:05 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define red "\033[1;31m"
#define green "\033[1;32m"
#define res "\033[0m"

#define RD 0
#define WR 1

//TODO integrar + expansion
static void	_heredoc(char *dlmt)
{
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
	while (42)
	{
		line = readline(green "here: doc > " res);
		if (!line)

			write(STDOUT_FILENO, "\n", 1);
		if (!line || !ft_strncmp(line, dlmt, ft_strlen(dlmt)))
			break ;
		write(pipefd[WR], line, ft_strlen(line));
		write(pipefd[WR], "\n", 1);
	}
	close(pipefd[WR]);
	//close(pipefd[RD]); //TODO cerrar el extremo de lectura??
	dup2(pipefd[RD], STDIN_FILENO);
}
