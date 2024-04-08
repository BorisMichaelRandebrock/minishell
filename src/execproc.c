/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:08 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/08 16:45:55 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

#define NUL_SZ		1
#define ARG0_SZ		1
#define TO_PROC		0
#define TO_SHELL	1
#define RD			0
#define WR			1

//TODO gestionar excepcion  msg: "bash: cacafruti: command not found"
static void	_child_procces(int pipes[2][2], char *exec_path, char **exec_args)
{
	if (!exec_path)
		exit(FAILURE);
	dup2(pipes[TO_PROC][RD], STDIN_FILENO);
	close(pipes[TO_PROC][RD]);
	dup2(pipes[TO_SHELL][WR], STDOUT_FILENO);

	//TODO borrar test
/* 	printf("- %s\n", exec_args[0]);
	printf("- %s\n", exec_args[1]); */

	execve(exec_path, exec_args, get_shell()->env);
}

static void	_parent_procces(t_cmd *cmd, int pipes[2][2], char *sbuffer)
{
	ssize_t	bytes_read;
	int		child_status;
	char	*child_exit_code;

	wait3(&child_status, 0, NULL);
	close(pipes[TO_SHELL][WR]);
	bytes_read = read(pipes[TO_SHELL][RD], sbuffer, BUF_1MB);
	close(pipes[TO_SHELL][RD]);
	sbuffer[bytes_read] = '\0';
	child_exit_code = ft_itoa(WEXITSTATUS(child_status));
	set_evar("?=", child_exit_code);
	sh_free(&child_exit_code);
	if (!cmd->to_pipe)
		printf("%s", sbuffer);
}

// TODO gestionar excepcion
static char	*_build_path(char *cmd_name)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1KB + NUL_SZ];

	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i] && !ft_fexists(buffer))
	{
		ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, splitted[i], BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, "/", BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, cmd_name, BUF_1KB + NUL_SZ);
		i++;
	}
	i = 0;
	while (splitted[i])
		sh_free(&splitted[i++]);
	sh_free(&splitted);
	if (ft_fexists(buffer) && *buffer)
		return (sh_guard(ft_strdup(buffer), NULL));
	return (NULL);
}

static char	**_args_to_array(t_cmd *cmd)
{
	char	**args;
	t_list	*argslst;
	size_t	list_sz;
	size_t	i;

	argslst = cmd->args;
	list_sz = ft_lstsize(argslst) + ARG0_SZ;
	if (list_sz == 1)
	{
		args = sh_calloc(1 + NUL_SZ, sizeof(char **));
		args[0] = cmd->tkn->str;
		args[1] = NULL;
		return (args);
	}
	args = sh_calloc(list_sz + NUL_SZ, sizeof(char **));
	i = 0;
	args[i++] = cmd->tkn->str;
	while (i < list_sz)
	{
		args[i++] = ((t_token *)argslst->content)->str;
		argslst = argslst->next;
	}
	args[i] = NULL;
	return (args);
}

//TODO excepcion comando no encontrado???  exec_path = null
void	try_process(t_cmd *cmd, char *sbuffer)
{
	char	*exec_path;
	char	**exec_args;
	int		pipes[2][2];
	pid_t	pid;

	pipe(pipes[TO_PROC]);
	pipe(pipes[TO_SHELL]);
	exec_args = _args_to_array(cmd);
	exec_path = _build_path(cmd->tkn->str);
	write(pipes[TO_PROC][WR], sbuffer, ft_strlen(sbuffer));
	close(pipes[TO_PROC][WR]);
	pid = fork();
	if (pid == 0)
		_child_procces(pipes, exec_path, exec_args);
	else if (exec_path)
		_parent_procces(cmd, pipes, sbuffer);
	sh_free(&exec_args);
	sh_free(&exec_path);
}
