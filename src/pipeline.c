/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/17 18:11:56 by fmontser         ###   ########.fr       */
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

//TODO hacer lecturas de FD ciclicas!
static void	_process_rd_in(t_list *rdrs_in, int to_proc_wr)
{
	t_token	*_rdr;

	if (!rdrs_in)
		return ;
	_rdr = rdrs_in->content;
	if (_rdr->type == RDIN)
	{
		while (rdrs_in->next)
			rdrs_in = rdrs_in->next;
		_rdr = rdrs_in->content;
		sh_fpstream(_rdr->str, to_proc_wr);
	}
	else if (_rdr->type == RDHDOC)
		invoke_heredoc(_rdr->str, to_proc_wr);
	close(to_proc_wr);
}

static int	_exec_cmd(t_cmd *cmd, int Bx_rd)
{
	int	Tx[2];
	int	Rx[2];
	int _out;
	int _in;

	_out = dup(STDOUT_FILENO);
	_in = dup(STDIN_FILENO);
	pipe(Tx);
	pipe(Rx);
	dup2(Tx[RD], STDIN_FILENO);
	dup2(Rx[WR], STDOUT_FILENO);
	sh_pprelay(Bx_rd, Tx[WR]);
	close(Tx[WR]);
	if (_try_builtin(cmd) == FAILURE)
		try_process(cmd);
	dup2(_in, STDIN_FILENO);
	dup2(_out, STDOUT_FILENO);
	close(Tx[RD]);
	close(Rx[WR]);
	return (Rx[RD]);
}

void		exec_pipeline(t_list *ppln)
{
	int		Bx[2];
	int		Rx_rd;
	t_cmd	*cmd;

	pipe(Bx);
	while(ppln)
	{
		cmd = ppln->content;
		close(Bx[WR]);
		Rx_rd = _exec_cmd(cmd, Bx[RD]);
		close(Bx[RD]);
		pipe(Bx);
		if (ppln->next)
			sh_pprelay(Rx_rd, Bx[WR]);
		else
			sh_pprelay(Rx_rd, 1); //TODO @@@@@@@@@@@ continuar implementando entradas y salidas
		close(Rx_rd);
		ppln = ppln->next;
	}
}
