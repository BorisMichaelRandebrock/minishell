/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/13 13:14:04 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
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


/*
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

//TODO hacer lecturas de FD ciclicas!
static void	_process_rd_in(t_list *rdrs_in, int to_proc_fd)
{
	int		input_fd;
	char	buffer[BUF_1KB + NUL_SZ];
	ssize_t	consumed;
	t_token	*_rdr;

	if (!rdrs_in)
		return ;
	input_fd = 0;
	ft_memset(buffer, '\0',BUF_1KB + NUL_SZ);
	_rdr = rdrs_in->content;
	if (_rdr->type == RDIN)
	{
		while (rdrs_in->next)
			rdrs_in = rdrs_in->next;
		_rdr = rdrs_in->content;
		input_fd = open(_rdr->str, O_RDONLY, 0777);
		consumed = read(input_fd, buffer, BUF_1KB);
		write(to_proc_fd, buffer, consumed);
	}
	else if (_rdr->type == RDHDOC)
		invoke_heredoc(_rdr->str, to_proc_fd);
	close(to_proc_fd);
	close(input_fd);
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
	while (ppln)
	{
		cmd = ppln->content;
		_process_rd_in(cmd->rdrs_in, to_proc[WR]);
		dup2(to_proc[RD], STDIN_FILENO);//TODO @@@@@@@ Ponerlo aqui funciona pero genera leaks!
		if (ppln->next)
		{
			cmd->is_piped = true;
			to_shell[WR] = dup2(to_shell[WR], STDOUT_FILENO); //TODO esto esta bien? nopE!!
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
