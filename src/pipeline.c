/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/21 17:52:12 by fmontser         ###   ########.fr       */
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
	if (cmd->is_piped || cmd->rdrs)
		fd = pipefd[WR];
	else
		ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(&_tkn), NULL));
	exit_code = ft_itoa((bltn)(cmd->args, fd));
	if (cmd->is_piped || cmd->rdrs)
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
		if (_cmd->rdrs)
			process_redirs(_cmd, shell_buffer);
		i = 0;
		_ppln = _ppln->next;
	}
}

static t_list *_add_redirection(t_list *tkn_lst, t_cmd *cmd)
{
	t_rdr	*rdr;
	t_token *tkn;

	tkn = tkn_lst->content;
	rdr = sh_calloc(1, sizeof(t_rdr));
	rdr->op = tkn;
	tkn_lst = tkn_lst->next;
	while(tkn_lst)
	{
		tkn = tkn_lst->content;
		if (tkn->type == ARG)
			ft_lstadd_back(&rdr->args, sh_guard(ft_lstnew(tkn), NULL));
		else if (tkn->type == PIPE)
			break ;
		else
		{
			ft_lstadd_back(&cmd->rdrs, sh_guard(ft_lstnew(rdr), NULL));
			_add_redirection(tkn_lst->next, cmd);
			break ;
		}
		tkn_lst = tkn_lst->next;
	}
	ft_lstadd_back(&cmd->rdrs, sh_guard(ft_lstnew(rdr), NULL));
	return (tkn_lst);
}


// echo hola > file  sfsdf| echo
void	run_pipeline(t_list *tkn_lst)
{
	t_shell	*sh;
	t_token	*_tkn;
	t_cmd	*cmd;
	t_list	*_lst;
	bool	rflag;

	rflag = false;
	_lst = tkn_lst;
	sh = get_shell();
	cmd = NULL;
	while (_lst)
	{
		_tkn = _lst->content;
		if (_tkn->type == CMD)
		{
			rflag = false;
			cmd = sh_calloc(1, sizeof(t_cmd));
			cmd->tkn = _tkn;
			cmd->is_piped = false;
			ft_lstadd_back(&sh->ppln, sh_guard(ft_lstnew(cmd), NULL));
		}
		else if (_tkn->type == ARG && !rflag)
			ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(_tkn), NULL));
		else if (_tkn->type != PIPE)
		{
 			if (!cmd)
			{
				cmd = sh_calloc(1, sizeof(t_cmd));
				cmd->tkn = _tkn;
				cmd->is_piped = false;
				ft_lstadd_back(&sh->ppln, sh_guard(ft_lstnew(cmd), NULL));
			}
			rflag = true;
			_lst = _add_redirection(_lst, cmd);
			continue ; //TODO recoger el avance, TEMA listas subrogadas
		}
		_lst = _lst->next;
	}
	_exec_pipeline(sh->ppln);
}
