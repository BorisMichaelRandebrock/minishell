/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:04 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/11 10:59:09 by brandebr         ###   ########.fr       */
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

static void	_heredoc(char *dlmt)
{
	char	*line;
	int		pipefd[2];
	int		fd_file;

	pipe(pipefd);
	fd_file = open("tempfile", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_file == -1)
	{
		printf(red "Error opening the file: %s\n" res, "tempfile");
		return ;
	}
	while (42)
	{
		line = readline(green "here: doc 📜 > " res);
		if (!line)
			write(STDOUT_FILENO, "NULL\n", 5);
		if (!line || !ft_strncmp(line, dlmt, ft_strlen(dlmt)))
			break ;
		//		if (!line || !strcmp(line, dlmt))
		write(fd_file, line, ft_strlen(line));
		write(fd_file, "\n", 1);
	}
	close(fd_file);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
