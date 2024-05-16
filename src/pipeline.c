/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/16 14:05:45 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_SZ		1
#define NUL_FD		-1
#define RD			0
#define WR			1

//TODO reservar pipes dinamicamente
static void _wait_execs(int nproc)
{
	int		child_status;
	char	*child_exit_code;

	while (nproc--)
	{
		wait3(&child_status, 0, NULL);
		child_exit_code = ft_itoa(WEXITSTATUS(child_status));
		set_evar("?=", child_exit_code);
		sh_free(&child_exit_code);
	}
}

void	exec_pipeline(t_list *ppln)
{
	int		pp[1024][2];
	t_cmd	*cmd;
	int		ppid;
	bool	gets_pipe;
	bool	sets_pipe;

	int		nproc = ft_lstsize(ppln);
	ppid = 0;
	pipe(pp[ppid]);
	gets_pipe = false;
	sets_pipe = false;
	while (ppln)
	{
		cmd = ppln->content;
		if (ppln->next)
			sets_pipe = true;
		else
			sets_pipe = false;
		pipe(pp[ppid + 1]);
		if (!try_builtin(cmd, pp, sets_pipe, ppid))
			try_process(cmd, pp, gets_pipe, sets_pipe, ppid);
		close(pp[ppid][WR]);
		close(pp[ppid][RD]);
		gets_pipe = true;
		ppid++;
		ppln = ppln->next;
	}
	close(pp[ppid][WR]);
	close(pp[ppid][RD]);
	_wait_execs(nproc);
}
