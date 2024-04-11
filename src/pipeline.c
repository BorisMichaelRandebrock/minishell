/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/11 18:17:41 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define NUL_SZ	1
#define TO_PROC		0
#define TO_SHELL	1
#define RD		0
#define WR		1

static bool	_try_builtin(t_cmd *cmd)
{
	static t_bltin	bltn_ptr[9] = {__echo, __export , __cd, __pwd,
		__unset, __env, __exit, __history, NULL};
	static char		*bltn_id[9] = {"echo","export", "cd", "pwd",
		"unset", "env", "exit", "history", NULL};
	int				i;
	size_t			cmp_sz;
	char	*exit_code;

	i = 0;
	while (bltn_id[i])
	{
		cmp_sz = ft_strlen(bltn_id[i]) + NUL_SZ;
		if (!ft_strncmp(cmd->tkn->str, bltn_id[i], cmp_sz))
		{
			exit_code = ft_itoa((bltn_ptr[i])(cmd->args));
			set_evar("?=", sh_guard(exit_code, NULL));
			sh_free(&exit_code);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

/* static void	_process_rd_in(t_cmd *cmd)
{
	while (cmd->rdrs_in)
	{
		cmd->rdrs_in->next;
	}
}

static void	_process_rd_out(t_cmd *cmd)
{
	while (cmd->rdrs_out)
	{
		cmd->rdrs_out->next;
	}
} */

//TODO cambiar el buffer a 1MB
void	_pipe_pass(int to_proc[2], int to_shell[2])
{
	char	buffer[BUF_1KB + NUL_SZ];
	ssize_t	consumed;

	ft_memset(buffer, '\0',BUF_1KB + NUL_SZ);
	consumed = read(to_shell[RD], buffer, BUF_1KB);
	if (consumed > 0)
		write (to_proc[WR], buffer, consumed);
	close(to_proc[WR]);
}


void	exec_pipeline(t_list *ppln)
{
	int		to_proc[2];
	int		to_shell[2];
	t_cmd	*cmd;
	int		_stdout;
	int		_stdin;

	pipe(to_proc);
	pipe(to_shell);
	_stdout = dup(STDOUT_FILENO);
	_stdin = dup(STDIN_FILENO);
	dup2(to_proc[RD], STDIN_FILENO);
	while (ppln)
	{
		cmd = ppln->content;
		if (ppln->next)
		{
			cmd->is_piped = true;
			to_shell[WR] = dup2(to_shell[WR], STDOUT_FILENO);
			if (_try_builtin(cmd) == FAILURE)
				try_process(cmd);
			_pipe_pass(to_proc, to_shell);
		}
		else
		{
			dup2(_stdout, STDOUT_FILENO);
			if (_try_builtin(cmd) == FAILURE)
				try_process(cmd);
			dup2(_stdin, STDIN_FILENO);
		}
		ppln = ppln->next;
	}
}
