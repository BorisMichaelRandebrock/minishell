/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:14:26 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/06 21:33:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define NUL_SZ	1
#define RD		0
#define WR		1

static void	_exec_builtin(t_bltin bltn, t_cmd *cmd, char *sbuffer)
{
	char	*exit_code;
	int		pipefd[2];
	int		fd;
	t_token	_tkn;

	_tkn.str = sbuffer;
	sbuffer[ft_strlen(sbuffer)] = '\0';
	pipe(pipefd);
	fd = STDOUT_FILENO;
	if (cmd->to_pipe || cmd->rdrs)
	{
		fd = pipefd[WR];
		ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(&_tkn), NULL));
	}
	exit_code = ft_itoa((bltn)(cmd->args, fd));
	if (cmd->to_pipe || cmd->rdrs)
	{
		read(pipefd[RD], sbuffer, BUF_1MB);
		sbuffer[ft_strlen(sbuffer)] = '\0';
		close(pipefd[RD]);
	}
	set_evar("?=", sh_guard(exit_code, NULL));
	sh_free(&exit_code);
}

bool	try_builtin(t_cmd *cmd, char *sbuffer)
{
	static t_bltin	bltn_ptr[9] = {__echo, __cd, __pwd, __export,
		__unset, __env, __exit, __history, NULL};
	static char		*bltn_id[9] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", "history", NULL};
	int				i;
	size_t			cmp_sz;

	i = 0;
	while (bltn_id[i])
	{
		cmp_sz = ft_strlen(bltn_id[i]) + NUL_SZ;
		if (!ft_strncmp(cmd->tkn->str, bltn_id[i], cmp_sz))
		{
			_exec_builtin(bltn_ptr[i], cmd, sbuffer);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}
