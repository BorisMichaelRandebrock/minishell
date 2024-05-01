/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/01 12:46:23 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_SZ	1
#define NUL_FD	-1
#define RD		0
#define WR		1

static bool	_try_builtin(t_cmd *cmd)
{
	static t_bltin	bltn_ptr[8] = {__echo, __export, __cd, __pwd,
		__unset, __env, __exit, NULL};
	static char		*bltn_id[8] = {"echo", "export", "cd", "pwd",
		"unset", "env", "exit", NULL};
	int				i;
	size_t			cmp_sz;
	char			*exit_code;

	i = 0;
	if (!cmd->tkn)
		return (FAILURE);
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

static void	_process_rd_out(t_list *rdrs_out, int rx_rd)
{
	t_token	*_rdr;
	int		fd;

	if (!rdrs_out)
		return ;
	while (rdrs_out)
	{
		_rdr = rdrs_out->content;
		if (_rdr->type == RDOUT)
			fd = open(_rdr->str, O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (_rdr->type == RDAPP)
			fd = open(_rdr->str, O_APPEND | O_CREAT | O_RDWR, 0777);
		rdrs_out = rdrs_out->next;
	}
	sh_pprelay(rx_rd, fd);
}

static void	_process_rd_in(t_list *rdrs_in, int tx_wr)
{
	t_token	*_rdr;

	if (!rdrs_in)
		return ;
	while (rdrs_in)
	{
		_rdr = rdrs_in->content;
		if (_rdr->type == RDIN && !rdrs_in->next)
			sh_fprelay(_rdr->str, tx_wr);
		else if (_rdr->type == RDHDOC)
		{
			if (!rdrs_in->next)
				invoke_heredoc(_rdr->str, tx_wr);
			else
				invoke_heredoc(_rdr->str, NUL_FD);
		}
		rdrs_in = rdrs_in->next;
	}
}

static int	_exec_cmd(t_cmd *cmd, int bx_rd)
{
	int	txp[2];
	int	rxp[2];
	int	_stdout;
	int	_stdin;

	_stdout = dup(STDOUT_FILENO);
	_stdin = dup(STDIN_FILENO);
	pipe(txp);
	pipe(rxp);
	if (cmd->rdrs_in)
		_process_rd_in(cmd->rdrs_in, txp[WR]);
	else
		sh_pprelay(bx_rd, txp[WR]);
	close(txp[WR]);
	dup2(rxp[WR], STDOUT_FILENO);
	dup2(txp[RD], STDIN_FILENO);
	if (_try_builtin(cmd) == FAILURE)
		try_process(cmd);
	close(txp[RD]);
	close(rxp[WR]);
	dup2(_stdin, STDIN_FILENO);
	dup2(_stdout, STDOUT_FILENO);	
	return (rxp[RD]);
}

void	exec_pipeline(t_list *ppln)
{
	int		bxp[2];
	int		rx_rd;
	t_cmd	*cmd;

	pipe(bxp);
	while (ppln)
	{
		cmd = ppln->content;
		if (sh_cmd_validation(cmd) == FAILURE)
			return ;
		close(bxp[WR]);
		rx_rd = _exec_cmd(cmd, bxp[RD]);
		close(bxp[RD]);
		pipe(bxp);
		if (ppln->next)
			sh_pprelay(rx_rd, bxp[WR]);
		else if (cmd->rdrs_out)
			_process_rd_out(cmd->rdrs_out, rx_rd);
		else
			sh_pprelay(rx_rd, STDOUT_FILENO);
		close(rx_rd);
		ppln = ppln->next;
	}
}
