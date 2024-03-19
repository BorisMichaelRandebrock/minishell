/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/19 19:59:05 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
 #include <sys/wait.h>
#include "minishell.h"

void	_exec_builtin(t_bltin bltn, t_cmd *cmd, char *shell_buffer)
{
	char	*exit_code;
	int		pipefd[2];
	int		fd;
	t_token	_tkn;

	_tkn.str = shell_buffer;
	shell_buffer[ft_strlen(shell_buffer)] = '\0';
	pipe(pipefd);
	fd = STDOUT_FILENO;
	if (cmd->is_piped)
		fd = pipefd[WR];
	ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(&_tkn), NULL));
	exit_code = ft_itoa((bltn)(cmd->args, fd));
	if (cmd->is_piped)
	{
		read(pipefd[RD], shell_buffer, BUF_1MB);
		shell_buffer[ft_strlen(shell_buffer)] = '\0';
		close(pipefd[RD]);
	}
	set_evar("?=", sh_guard(exit_code, NULL));
	free(exit_code);
}

static char	_to_lower(unsigned int ignore, char c)
{
	(void)ignore;
	return (ft_tolower(c));
}

//TODO al ejecutar un builtin o un proceso nuevo hay que actualizar la variable de entorno $_ que recoge el ultimo ejecutado
//TODO @@@@@@@@ rdirecciones

/* echo DDDX > file >> file2 | cat

es en realidad una especi de fork por cada operador...

*/


static void	_exec_pipeline(t_list	*ppln)
{
	static t_bltin	bltn_ptr[9] = {__echo, __cd, __pwd, __export,
		__unset, __env, __exit, __history, NULL};
	static char		*bltn_id[9] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", "history", NULL};
	char			shell_buffer[BUF_1MB + NUL_SZ];
	t_cmd			*_cmd;
	int				i;
	t_list			*_ppln;

	ft_memset(shell_buffer, '\0', BUF_1MB);
	_ppln = ppln;
	i = 0;
	while (_ppln)
	{
		_cmd = _ppln->content;
		_cmd->tkn->str = sh_guard(ft_strmapi(_cmd->tkn->str, _to_lower), _cmd->tkn->str);
		if (_ppln->next)
			_cmd->is_piped = true;
		while (bltn_id[i])
		{
			if (!ft_strncmp(_cmd->tkn->str, bltn_id[i], ft_strlen(bltn_id[i]) + NUL_SZ))
				_exec_builtin(bltn_ptr[i], _cmd, shell_buffer);
			i++;
		}
		i = 0;
		_ppln = _ppln->next;
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
			cmd->tkn = _tkn;
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
