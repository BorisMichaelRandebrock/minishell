/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:08 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/02 19:04:10 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#define RD 0
#define WR 1

//TODO read exception handling...
void	try_process(t_cmd *cmd, char *sbuffer)
{
	char	*path;
	char	**args;
	int		pipefd[2];
	pid_t	pid;
	//int		exit_code;
	ssize_t	bytes_read;
	t_list	*_args;
	int		i;
	int		size;

	size = ft_lstsize(cmd->args)+ 1;
	args = sh_calloc(size, sizeof(char **));
	i = 0;
	_args = cmd->args;
	while (_args)
	{
		args[i] = ((t_token *)_args->content)->str;
		i++;
		_args = _args->next;
	}
	args[i] = NULL;

	pipe(pipefd);
	path = cmd->tkn->str;
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[RD]);
		dup2(pipefd[WR], STDOUT_FILENO);
		close(pipefd[WR]);
		execve(path, args, get_shell()->env); //TODO EXECVE @@@@@@@@@ no encuentra ejecutables en el path
	}
	else
	{
		waitpid(pid, NULL, 0);
		//wait3(NULL, 0, NULL); //TODO quizas es WAIT el que falla???
		close(pipefd[WR]);
		bytes_read = read(pipefd[RD], sbuffer, BUF_1MB);
		sbuffer[bytes_read] = '\0';
		printf("%s", sbuffer);
		free(args);
	}
}
