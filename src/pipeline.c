/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/13 11:08:47 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
 #include <sys/wait.h>
#include "minishell.h"

#define LAST_EXIT_EVAR "?"

void	_exec_builtin(t_bltin bltn, t_cmd *cmd, char *shell_buffer)
{
	int		exit_code;
	int		pipefd[2];
	int		fd;
	t_token	_tkn;

	_tkn.str = shell_buffer;
	pipe(pipefd);
	fd = STDOUT_FILENO;
	if (cmd->is_piped)
		fd = pipefd[WR];
	else if (!cmd->is_piped && *_tkn.str)
		ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(&_tkn), NULL));
	exit_code = (bltn)(cmd->args, fd);
	if (cmd->is_piped)
	{
		read(pipefd[RD], shell_buffer, BUFSIZ);
		close(pipefd[RD]);
		set_evar(LAST_EXIT_EVAR, sh_guard(ft_itoa(exit_code), NULL));
	}
}

static char	_to_lower(unsigned int ignore, char c)
{
	(void)ignore;
	return (ft_tolower(c));
}

static void	_exec_pipeline(t_list	*ppln)
{
	static t_bltin	bltn_ptr[7] = {__echo, __cd, __pwd, __export,
		__unset, __env, __exit};
	static char		*bltn_id[7] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};
	char			shell_buffer[BUFSIZ];
	t_cmd			*_cmd;
	int				i;

	i = 0;
	while (ppln)
	{
		_cmd = ppln->content;
		_cmd->cmd->str = sh_guard(ft_strmapi(_cmd->cmd->str, _to_lower), NULL);
		if (ppln->next)
			_cmd->is_piped = true;
		while (bltn_id[i])
		{
			if (!ft_strncmp(_cmd->cmd->str, bltn_id[i], ft_strlen(bltn_id[i])))
				_exec_builtin(bltn_ptr[i], _cmd, shell_buffer);
			i++;
		}
		i = 0;
		ppln = ppln->next;
	}
}

static void	_skip_redirection(t_list *lst)
{
	t_token	*tkn;

	tkn = lst->content;
	while ((tkn->type != OP && tkn->optype != PIPE) || lst)
		lst = lst->next;
}

void	run_pipeline(t_list *tkn_lst)
{
	t_shell	*sh;
	t_token	*_tkn;
	t_cmd	*cmd;
	t_list	*_lst;

	_lst = tkn_lst;
	sh = get_shell();
	while (_lst)
	{
		_tkn = _lst->content;
		if (_tkn->type == CMD)
		{
			cmd = sh_calloc(1, sizeof(t_cmd));
			cmd->cmd = _tkn;
			cmd->is_piped = false;
			ft_lstadd_back(&sh->ppln, sh_guard(ft_lstnew(cmd), NULL));
		}
		else if (_tkn->type == ARG)
			ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(_tkn), NULL));
		else if (_tkn->type == OP && _tkn->optype != PIPE)
			_skip_redirection(_lst);
		if (_lst)
			_lst = _lst->next;
	}
	_exec_pipeline(sh->ppln);
}
