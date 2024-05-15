/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/15 18:20:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include "minishell.h"

#define NUL_SZ		1
#define NUL_FD		-1
#define RD			0
#define WR			1
#define CHILD_PID	0
#define MAX_PROC

//TODO check
/* static void	_exec_cmd(t_cmd *cmd, int pp[2][2], t_list * ppln, )
{
	pid_t	pid;
	int		bytes_left;
	

	pid = fork();
	if (pid == CHILD_PID)
	{
		close(pp[i][WR]);
		ioctl(pp[i][RD], FIONREAD, &bytes_left);
		if (bytes_left > 0)
			dup2(pp[i][RD], STDIN_FILENO);
		else
			close(pp[i][RD]);

		close(pp[i + 1][RD]);
		if (ppln->next)
			dup2(pp[i + 1][WR], STDOUT_FILENO);
		else
			close(pp[i + 1][WR]);
		try_process(cmd);
	}
	close(pp[i][WR]);
	close(pp[i][RD]);
} */

// cat -e lorem | cat -e | cat -e > fout
//TODO redir-in priority over pipe
//TODO MAGIC NUMBERS


static bool	_process_rd_in(t_list *rdrs_in, int pp_wr)
{
	t_token	*_rdr;

	if (!rdrs_in)
		return (false);
	while (rdrs_in)
	{
		_rdr = rdrs_in->content;
		if (!validate_rdrin(_rdr))
		{
			//get_shell()->_abort = true;
			return (false);
		}
		if (_rdr->type == RDIN && !rdrs_in->next)
			sh_fprelay(_rdr->str, pp_wr);
		else if (_rdr->type == RDHDOC)
		{
			if (!rdrs_in->next)
				invoke_heredoc(_rdr->str, pp_wr);
			else
				invoke_heredoc(_rdr->str, NUL_FD);
		}
		rdrs_in = rdrs_in->next;
	}
	return (true);
}

static void	_process_rd_out(t_list *rdrs_out, int pp_wr)
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
	dup2(fd, pp_wr);
}

void	exec_pipeline(t_list *ppln)
{
	int		pp[1024][2];
	t_cmd	*cmd;
	pid_t	pid;
	bool	gets_pipe;
	bool	sets_pipe;


	pipe(pp[0]);
	cmd = ppln->content;
		
	pipe(pp[1]);

	gets_pipe = false;
	sets_pipe = true;
	pid = fork();
	if (pid == CHILD_PID)
	{
 		if (cmd->rdrs_in)
		{
			pipe(pp[0]);
			_process_rd_in(cmd->rdrs_in, pp[0][WR]);
			gets_pipe = true;
		}
		close(pp[0][WR]);
		if (gets_pipe)
			dup2(pp[0][RD], STDIN_FILENO);
		else
			close(pp[0][RD]);



		if (cmd->rdrs_out)
		{
			_process_rd_out(cmd->rdrs_out, pp[1][WR]);
			sets_pipe = true;
		}
		close(pp[1][RD]);
		if (sets_pipe)
			dup2(pp[1][WR], STDOUT_FILENO);
		else
			close(pp[1][WR]);

		try_process(cmd);
	}
	close(pp[0][WR]);
	close(pp[0][RD]);

	close(pp[1][WR]);
	close(pp[1][RD]);

	wait(NULL);
/* 
	cmd = ppln->next->content;
	pipe(pp[2]);


	gets_pipe = true;
	sets_pipe = false;
	pid = fork();
	if (pid == CHILD_PID)
	{
		if (cmd->rdrs_in)
		{
			pipe(pp[1]);
			_process_rd_in(cmd->rdrs_in, pp[1][WR]);
			gets_pipe = true;
		}
		close(pp[1][WR]);
		if (gets_pipe)
			dup2(pp[1][RD], STDIN_FILENO);
		else
			close(pp[1][RD]);

		if (cmd->rdrs_out)
		{
			_process_rd_out(cmd->rdrs_out, pp[2][WR]);
			sets_pipe = true;
		}
		close(pp[2][RD]);
		if (sets_pipe)
			dup2(pp[2][WR], STDOUT_FILENO);
		else
			close(pp[2][WR]);
		try_process(cmd);
	}
	close(pp[1][WR]);
	close(pp[1][RD]); */

/* 	close(pp[2][WR]);
	close(pp[2][RD]); */
/*
	cmd = ppln->next->next->content;
	pipe(pp[3]);

	gets_pipe = true;
	sets_pipe = false;
	pid = fork();
	if (pid == CHILD_PID)
	{
		//gets_pipe = _process_rd_in(cmd->rdrs_in, pp[2][WR]); //tst rdrin
		close(pp[2][WR]);
		if (gets_pipe)
			dup2(pp[2][RD], STDIN_FILENO);
		else
			close(pp[2][RD]);

		close(pp[3][RD]);
		if (sets_pipe)
			dup2(pp[3][WR], STDOUT_FILENO);
		else
			close(pp[3][WR]);
		try_process(cmd);
	}
	close(pp[2][WR]);
	close(pp[2][RD]);
	close(pp[3][WR]);
	close(pp[3][RD]);*/
	
	//wait(NULL);
	//wait(NULL);
	//wait(NULL);
}





//TODO integrar wait + exit status

/* 

		wait3(&child_status, 0, NULL);
		child_exit_code = ft_itoa(WEXITSTATUS(child_status));
		set_evar("?=", child_exit_code);
		sh_free(&child_exit_code);

 */


//TODO check validation
//TODO check pipe or redir priority
/* static void	_process_rd_in(t_list *rdrs_in, int pp_wr)
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
			sh_fprelay(_rdr->str, pp_wr);
		else if (_rdr->type == RDHDOC)
		{
			if (!rdrs_in->next)
				invoke_heredoc(_rdr->str, pp_wr);
			else
				invoke_heredoc(_rdr->str, NUL_FD);
		}
		rdrs_in = rdrs_in->next;
	}
} */

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