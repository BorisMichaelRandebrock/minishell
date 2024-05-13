/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/13 17:22:53 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_SZ	1
#define NUL_FD	-1
#define RD		0
#define WR		1

static bool	_try_builtin(t_cmd *cmd, int pp[2][2], t_list *prev, t_list *ppln)
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
		return (false);
	while (bltn_id[i])
	{
		cmp_sz = ft_strlen(bltn_id[i]) + NUL_SZ;
		if (!ft_strncmp(cmd->tkn->str, bltn_id[i], cmp_sz))
		{
			(void)prev;
			if (ppln->next)
				dup2(pp[0][WR], STDOUT_FILENO);
			exit_code = ft_itoa((bltn_ptr[i])(cmd->args));
			set_evar("?=", sh_guard(exit_code, NULL));
			sh_free(&exit_code);
			return (true);
		}
		i++;
	}
	return (false);
}

static void	_exec_cmd(t_cmd *cmd, int pp[2][2], t_list *prev, t_list *ppln)
{
	pid_t	pid;

	if (!_try_builtin(cmd, pp, prev, ppln)) //TODO todo mal!!! @@@@
	{
		pid = fork();
		if (pid == 0)
		{
			close(pp[0][WR]);
			if (prev)
				dup2(pp[0][RD], STDIN_FILENO);
			else
				close(pp[0][RD]);

			close(pp[1][RD]);
			if (ppln->next)
				dup2(pp[1][WR], STDOUT_FILENO);
			else
				close(pp[1][WR]);
			try_process(cmd);
		}
		pp[0][RD] = pp[1][RD];
		pp[0][WR] = pp[1][WR];
	}
}


// cat -e lorem | cat -e | cat -e > fout
void	exec_pipeline(t_list *ppln)
{
	int		pp[2][2];
	int		ppln_sz;
	t_cmd	*cmd;
	t_list	*prev;

	ppln_sz = ft_lstsize(ppln);
	prev = NULL;
	pipe(pp[0]);
	while (ppln)
	{
		cmd = ppln->content;
		pipe(pp[1]);
		close(pp[0][WR]);
		_exec_cmd(cmd, pp, prev, ppln);
		close(pp[0][RD]);
		prev = ppln->content;
		ppln = ppln->next;
	}
	while (ppln_sz--)
		wait(NULL);
}





//TODO integrar wait + exit status

/* 

		wait3(&child_status, 0, NULL);
		child_exit_code = ft_itoa(WEXITSTATUS(child_status));
		set_evar("?=", child_exit_code);
		sh_free(&child_exit_code);

 */


/* static void	_process_rd_out(t_list *rdrs_out, int rx_rd)
{
	t_token	*_rdr;
	int		fd;

	if (!rdrs_out)
		return ;
	while (rdrs_out)
	{
		_rdr = rdrs_out->content;
		if (!validate_rdrout(_rdr))
		{
			//get_shell()->_abort = true;	
			return ;
		}
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
		if (!validate_rdrin(_rdr))
		{
			//get_shell()->_abort = true;
			return ;
		}
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
}*/