/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:08 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/17 15:50:38 by fmontser         ###   ########.fr       */
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
#define PP_GET		0
#define PP_SET		1

static char	*_build_path(char *cmd_name)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1KB + NUL_SZ];

	if (sh_fexists(cmd_name))
		return (sh_guard(ft_strdup(cmd_name), NULL));
	if (!get_evar("PATH="))
		return (sh_guard(ft_strdup(""), NULL));
	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i] && !sh_fexists(buffer))
	{
		ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, splitted[i++], BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, "/", BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, cmd_name, BUF_1KB + NUL_SZ);
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

static void	_child_process_input(t_cmd *cmd, int **pp, bool *status, int ppid)
{
	if (cmd->rdrs_in)
	{
		pipe(pp[ppid]);
		if (!process_rd_in(cmd->rdrs_in, pp[ppid][WR]))
			sh_free_exit(FAILURE);
		status[PP_GET] = true;
	}
	close(pp[ppid][WR]);
	if (status[PP_GET])
		dup2(pp[ppid][RD], STDIN_FILENO);
	else
		close(pp[ppid][RD]);
}

static void	_child_process_output(t_cmd *cmd, int **pp, bool *status, int ppid)
{
	if (cmd->rdrs_out)
	{
		if (!process_rd_out(cmd->rdrs_out))
			sh_free_exit(FAILURE);
		close(pp[ppid + 1][RD]);
		close(pp[ppid + 1][WR]);
	}
	else
	{
		close(pp[ppid + 1][RD]);
		if (status[PP_SET])
			dup2(pp[ppid + 1][WR], STDOUT_FILENO);
		else
			close(pp[ppid + 1][WR]);
	}
}

void	try_process(t_cmd *cmd, int **pp, bool *status, int ppid)
{
	pid_t	pid;
	char	*exec_path;
	char	**exec_args;

	if (!cmd->tkn || !validate_cmd(cmd))
	{
		process_rd_out_empty(cmd->rdrs_out);
		return ;
	}
	exec_args = _args_to_array(cmd);
	exec_path = _build_path(cmd->tkn->str);
	pid = fork();
	if (pid == CHILD_PID)
	{
		_child_process_input(cmd, pp, status, ppid);
		_child_process_output(cmd, pp, status, ppid);
		execve(exec_path, exec_args, get_shell()->sys_env);
	}
	sh_free(&exec_args);
	sh_free(&exec_path);
}
