/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:29:08 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/05 16:30:09 by fmontser         ###   ########.fr       */
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
	char	*exec_path;
	char	**exec_args;
	int		pipe_to_proc[2];
	int		pipe_to_shell[2];
	pid_t	pid;
	ssize_t	bytes_read;
	int		child_status;
	char	*child_exit_code;
	(void)bytes_read;
	(void)sbuffer;

	pipe(pipe_to_proc);
	pipe(pipe_to_shell);
	exec_args = _args_to_array(cmd);
	exec_path = _build_path(cmd->tkn->str);
	write(pipe_to_proc[WR], sbuffer, ft_strlen(sbuffer)); //BUG FIXED explicacion, un proceso no puede hacerse "input" a si mismo!
	close(pipe_to_proc[WR]);
	pid = fork();
	if (pid == 0)
	{
		if (!exec_path)
			exit(FAILURE); //TODO gestionarexcepcion comando no encontrado msg: "bash: cacafruti: command not found"
		dup2(pipe_to_proc[RD], STDIN_FILENO);
		dup2(pipe_to_shell[WR], STDOUT_FILENO);
		execve(exec_path, exec_args, get_shell()->env);
	}
	else if (exec_path)
	{
		wait3(&child_status, 0, NULL);
		close(pipe_to_shell[WR]);
		bytes_read = read(pipe_to_shell[RD], sbuffer, BUF_1MB);
		close(pipe_to_shell[RD]);
		sbuffer[bytes_read] = '\0';
		child_exit_code = ft_itoa(WEXITSTATUS(child_status));
		set_evar("?=", child_exit_code);
		sh_free(&child_exit_code);
		if (!cmd->to_pipe)
			printf("%s", sbuffer);
	}
	sh_free(&exec_args);
	sh_free(&exec_path);
	//TODO else excepcion comando no encontrado??? se hace aqui ?
}
