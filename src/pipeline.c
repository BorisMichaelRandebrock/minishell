/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/09 17:19:48 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define NUL_SZ	1
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

void	exec_pipeline(t_list *ppln)
{
	int		spipe[2];
	t_cmd	*cmd;
	int		_stdout;
	int		_stdin;

	pipe(spipe);
	_stdout = dup(STDOUT_FILENO);
	_stdin = dup(STDIN_FILENO);
	while (ppln)
	{
		cmd = ppln->content;
		if (ppln->next)
		{
			dup2(spipe[WR], STDOUT_FILENO);
			dup2(spipe[RD], STDIN_FILENO);
		}
		_try_builtin(cmd);
		//TODO procesos!
		close(spipe[WR]);
		dup2(_stdout, STDOUT_FILENO);
		ppln = ppln->next;
	}
	close(spipe[RD]);
	dup2(_stdin, STDIN_FILENO);
}

