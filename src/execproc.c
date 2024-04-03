/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:08 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/03 17:14:21 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"

#define IDX_OFFST 1
#define NUL_SZ 1
#define ARG0_SZ 1
#define RD 0
#define WR 1

static void	_child_procces(int *pipefd, char *execpath, char **execargs)
{
	close(pipefd[RD]);
	dup2(pipefd[WR], STDOUT_FILENO);
	close(pipefd[WR]);
	if (execpath)
		execve(execpath, execargs, get_shell()->env);
}

static void	_parent_procces(int	*pipefd, char *execpath, char *sbuffer)
{
	ssize_t	bytes_read;
	int		child_status;
	char	*child_exit_code;

	if (execpath)
	{
		wait3(&child_status, 0, NULL);
		child_exit_code = ft_itoa(WEXITSTATUS(child_status));
		set_evar("?=", child_exit_code);
		sh_free(&child_exit_code);
	}
	close(pipefd[WR]);
	bytes_read = read(pipefd[RD], sbuffer, BUF_1MB);
	close(pipefd[RD]);
	sbuffer[bytes_read] = '\0';
}

// TODO gestionar excepcion
static char	*_build_path(char *cmd_name)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1MB + NUL_SZ] = {0};

	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i] && !ft_fexists(buffer))
	{
		ft_memset(buffer, '\0', BUF_1MB + NUL_SZ);
		ft_strlcat(buffer, splitted[i], BUF_1MB + NUL_SZ);
		ft_strlcat(buffer, "/", BUF_1MB + NUL_SZ);
		ft_strlcat(buffer, cmd_name, BUF_1MB + NUL_SZ);
		i++;
	}
	i = 0;
	while (splitted[i])
		sh_free(&splitted[i++]);
	sh_free(&splitted);
	if (ft_fexists(buffer))
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
	if (list_sz < 2)
	{
		args = sh_calloc(1 + NUL_SZ, sizeof(char **));
		args[0] = "";
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

//TODO read exception handling...
void	try_process(t_cmd *cmd, char *sbuffer)
{
	char	*execpath;
	char	**execargs;
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	execargs = _args_to_array(cmd);
	execpath = _build_path(cmd->tkn->str);
	pid = fork();

	if (!cmd->is_piped)
		//TODO @@@@@ comunicacioni entre procesos (no buitin) no funciona!!!!!
		//write(pipefd[WR], sbuffer, ft_strlen(sbuffer));
		//ft_memset(sbuffer, '\0', ft_strlen(sbuffer));
	if (pid == 0)
		_child_procces(pipefd, execpath, execargs);
	else
	{
		_parent_procces(pipefd, execpath, sbuffer);
		if (!cmd->is_piped && !cmd->rdrs)
			write(STDOUT_FILENO, sbuffer, ft_strlen(sbuffer));
		sh_free(&execargs);
		sh_free(&execpath);
	}
}
