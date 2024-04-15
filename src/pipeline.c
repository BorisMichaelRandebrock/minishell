/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/15 18:56:51 by fmontser         ###   ########.fr       */
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


void	exec_pipeline(t_list *ppln)
{
	t_cmd	*cmd;
	int		to_proc[2];
	int		to_shell[2];
	int		_stdout;
	int		_stdin;


	pipe(to_proc);
	pipe(to_shell);
	_stdout = dup(STDOUT_FILENO);
	_stdin = dup(STDIN_FILENO);

	while (ppln)
	{
		cmd = ppln->content;
		if (ppln->next)
		{
			dup2(to_shell[WR], STDOUT_FILENO);
			if (_try_builtin(cmd) == FAILURE)
				try_process(cmd);
			close(to_shell[WR]);
			dup2(_stdout, STDOUT_FILENO);
			sh_ppstream(to_shell[RD], to_proc[WR]);
			//TODO @@@@@@@ continuar mplementado pipeline!
		}
		else
		{

		}
		ppln = ppln->next;
	}
}


//TODO @@@@@@@@@ pipes encadenados no funcionan ej.>  echo hola $USER | cat -e | wc -l
//TODO @@@@@@@ necesario replantear el flujo de datos
//TODO @@@@@@@ añadir lectura sin limite de buffer para archivos!!!
/* void	exec_pipeline(t_list *ppln)
{
	t_cmd	*cmd;
	int		to_proc[2];
	int		to_shell[2];
	int		_stdout;
	int		_stdin;
	int		swap_sh;
	int		swap_pc;

	pipe(to_proc);
	pipe(to_shell);
	_stdout = dup(STDOUT_FILENO);
	_stdin = dup(STDIN_FILENO);
	while (ppln)
	{
		cmd = ppln->content;
		//_process_rd_in(cmd->rdrs_in, to_proc[WR]);

		swap_pc = dup(to_proc[WR]); // dup amarillo
		close(to_proc[WR]);
		dup2(to_proc[RD], STDIN_FILENO); // protege STD_IN
		if (ppln->next)
		{
			dup2(to_shell[WR], STDOUT_FILENO);
			if (_try_builtin(cmd) == FAILURE)
				try_process(cmd);
			swap_sh = dup(to_shell[WR]); // dup azul
			close(to_shell[WR]);
			to_proc[WR] = swap_pc; // swap amarillo
			to_shell[WR] = swap_sh; // swap azul
			sh_ppstream(to_shell[RD], to_proc[WR]);

		}
		else
		{
			dup2(_stdout, STDOUT_FILENO); // protege STD_OUT
			if (_try_builtin(cmd) == FAILURE)
				try_process(cmd);
			dup2(_stdin, STDIN_FILENO);
		}
		ppln = ppln->next;
	}
} */
