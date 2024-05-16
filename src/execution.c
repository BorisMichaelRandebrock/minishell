/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:08 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/16 18:57:38 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "minishell.h"

#define NUL_SZ		1
#define ARG0_SZ		1
#define TO_PROC		0
#define TO_SHELL	1
#define RD			0
#define WR			1
#define CHILD_PID	0
#define NUL_FD		-1

static char	*_build_path(char *cmd_name)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1KB + NUL_SZ];

	if (sh_fexists(cmd_name))
		return (sh_guard(ft_strdup(cmd_name), NULL));
	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i] && !sh_fexists(buffer))
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
	if (sh_fexists(buffer) && *buffer)
		return (sh_guard(ft_strdup(buffer), NULL));
	return (sh_guard(ft_strdup(""), NULL));
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

//TODO Ante un comando invalido, las redirecciones de SALIDA deben aplicarse igualmente, haya pipe o no.
void	try_process(t_cmd *cmd, int **pp, int gets_pipe, int sets_pipe, int ppid)
{
	pid_t	pid;
	char	*exec_path;
	char	**exec_args;

	if (!cmd->tkn)
		return ;
	exec_args = _args_to_array(cmd);
	exec_path = _build_path(cmd->tkn->str);
	pid = fork();
	if (pid == CHILD_PID)
	{
		//IN
		if (cmd->rdrs_in)
		{
			pipe(pp[ppid]);
			process_rd_in(cmd->rdrs_in, pp[ppid][WR]);
			gets_pipe = true;
		}
		close(pp[ppid][WR]);
		if (gets_pipe)
			dup2(pp[ppid][RD], STDIN_FILENO);
		else
			close(pp[ppid][RD]);
			
		//OUT
		if (cmd->rdrs_out)
		{
			process_rd_out(cmd->rdrs_out);
			close(pp[ppid + 1][RD]);
			close(pp[ppid + 1][WR]);
		}
		else
		{
			close(pp[ppid + 1][RD]);
			if (sets_pipe)
				dup2(pp[ppid + 1][WR], STDOUT_FILENO);
			else
				close(pp[ppid + 1][WR]);
		}
		execve(exec_path, exec_args, get_shell()->env);
	}
	sh_free(&exec_args);
	sh_free(&exec_path);
}
