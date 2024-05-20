/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/20 11:54:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_SZ		1
#define NUL_FD		-1
#define RD			0
#define WR			1
#define PP_GET		0
#define PP_SET		1
#define HEADER_PIPE	1

static void	_wait_execs(void)
{
	int		_nproc_nb;
	t_list	*_ppln;
	t_cmd	*_cmd;
	int		child_status;
	char	*child_exit_code;

	_ppln = get_shell()->ppln;
	_nproc_nb = 0;
	while (_ppln)
	{
		_cmd = _ppln->content;
		if (!is_builtin(_cmd))
			_nproc_nb++;
		_ppln = _ppln->next;
	}
	while (_nproc_nb--)
	{
		wait3(&child_status, 0, NULL);
		child_exit_code = ft_itoa(WEXITSTATUS(child_status));
		set_evar("?=", child_exit_code);
		sh_free(&child_exit_code);
	}
}

static void	_free_pipes(int **pp, int nproc)
{
	int	i;

	i = 0;
	while (i < nproc)
		sh_free(&pp[i++]);
	sh_free(&pp);
}

static int	**_alloc_pipes(int *nproc)
{
	int	**pp;
	int	i;
	int	_nproc;

	i = 0;
	_nproc = ft_lstsize(get_shell()->ppln) + HEADER_PIPE;
	pp = sh_calloc(_nproc, sizeof(int *));
	while (i < _nproc)
		pp[i++] = sh_calloc(2, sizeof(int));
	*nproc = _nproc;
	return (pp);
}

static void	_exec_cmd(t_list *ppln, bool *status, int **pp, int *ppid)
{
	t_cmd	*cmd;
	int		_ppid;

	cmd = ppln->content;
	_ppid = *ppid;
	if (ppln->next)
		status[PP_SET] = true;
	else
		status[PP_SET] = false;
	pipe(pp[_ppid + 1]);
	if (!try_builtin(cmd, pp, status, _ppid))
		try_process(cmd, pp, status, _ppid);
	close(pp[_ppid][WR]);
	close(pp[_ppid][RD]);
	status[PP_GET] = true;
	(*ppid)++;
}

void	exec_pipeline(t_list *ppln)
{
	int		**pp;
	int		ppid;
	bool	status[2];
	int		nproc;

	pp = _alloc_pipes(&nproc);
	ppid = 0;
	pipe(pp[ppid]);
	status[PP_GET] = false;
	status[PP_SET] = false;
	while (ppln)
	{
		_exec_cmd(ppln, status, pp, &ppid);
		ppln = ppln->next;
	}
	close(pp[ppid][WR]);
	close(pp[ppid][RD]);
	_wait_execs();
	_free_pipes(pp, nproc);
}
