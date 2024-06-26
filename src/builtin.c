/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:22:25 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/20 11:42:39 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define WR	1
#define PP_SET		1

t_bltin	is_builtin(t_cmd *cmd)
{
	static t_bltin	bltn_ptr[8] = {__echo, __export, __cd, __pwd,
		__unset, __env, __exit, NULL};
	static char		*bltn_id[8] = {"echo", "export", "cd", "pwd",
		"unset", "env", "exit", NULL};
	int				i;
	size_t			cmp_sz;

	i = 0;
	if (!cmd->tkn)
		return (NULL);
	while (bltn_id[i])
	{
		cmp_sz = ft_strlen(bltn_id[i]) + NUL_SZ;
		if (!ft_strncmp(cmd->tkn->str, bltn_id[i], cmp_sz))
			return (bltn_ptr[i]);
		i++;
	}
	return (NULL);
}

bool	try_builtin(t_cmd *cmd, int **pp, bool *status, int ppid)
{
	t_bltin	bltin;
	int		_stdout;

	_stdout = dup(STDOUT_FILENO);
	if (!cmd->tkn)
		return (false);
	bltin = is_builtin(cmd);
	if (!bltin)
		return (false);
	if (cmd->rdrs_out)
	{
		if (process_rd_out(cmd->rdrs_out))
			set_bltin_exit_code((bltin)(cmd->args));
		dup2(_stdout, STDOUT_FILENO);
	}
	else if (status[PP_SET])
	{
		dup2(pp[ppid + 1][WR], STDOUT_FILENO);
		set_bltin_exit_code((bltin)(cmd->args));
		dup2(_stdout, STDOUT_FILENO);
	}
	else
		set_bltin_exit_code((bltin)(cmd->args));
	return (true);
}
