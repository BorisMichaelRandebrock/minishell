/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/07 12:00:28 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static char	_to_lower(unsigned int ignore, char c)
{
	(void)ignore;
	return (ft_tolower(c));
}

static void	_exec_pipeline(void)
{
	char	sbuffer[BUF_1MB + NUL_SZ];
	t_cmd	*_cmd;
	t_list	*_ppln;
	int		i;

	ft_memset(sbuffer, '\0', BUF_1MB);
	_ppln = get_shell()->ppln;
	i = 0;
	while (_ppln)
	{
		_cmd = _ppln->content;
		_cmd->tkn->str = sh_guard(ft_strmapi(_cmd->tkn->str, _to_lower),
				_cmd->tkn->str);
		if (_ppln->next)
		{
			_cmd->to_pipe = true;
			((t_cmd *)_ppln->next->content)->from_pipe = true;
		}
		if (try_builtin(_cmd, sbuffer) == FAILURE)
			try_process(_cmd, sbuffer);
		if (_cmd->rdrs)
			process_redirs(_cmd->rdrs, sbuffer);
		i = 0;
		_ppln = _ppln->next;
	}
}

static t_cmd	*_add_cmd(t_token *tkn, bool *rdrflag)
{
	t_shell	*sh;
	t_cmd	*cmd;

	if (rdrflag)
		*rdrflag = false;
	sh = get_shell();
	cmd = sh_calloc(1, sizeof(t_cmd));
	cmd->tkn = tkn;
	cmd->to_pipe = false;
	cmd->from_pipe = false;
	ft_lstadd_back(&sh->ppln, sh_guard(ft_lstnew(cmd), NULL));
	return (cmd);
}

static t_list	*_add_redirection(t_list *tknlst, t_cmd *cmd)
{
	t_rdr	*rdr;
	t_token	*tkn;

	tkn = tknlst->content;
	if (!cmd)
		cmd = _add_cmd(tkn, NULL);
	rdr = sh_calloc(1, sizeof(t_rdr));
	rdr->op = tkn;
	ft_lstadd_back(&cmd->rdrs, sh_guard(ft_lstnew(rdr), NULL));
	tknlst = tknlst->next;
	while (tknlst)
	{
		tkn = tknlst->content;
		if (tkn->type == ARG)
			ft_lstadd_back(&rdr->args, sh_guard(ft_lstnew(tkn), NULL));
		else if (tkn->type == PIPE)
			break ;
		else if (tkn->type != CMD)
		{
			tknlst = _add_redirection(tknlst, cmd);
			break ;
		}
		tknlst = tknlst->next;
	}
	return (tknlst);
}

void	run_pipeline(t_list *tknlst)
{
	t_token	*_tkn;
	t_cmd	*cmd;
	t_list	*_lst;
	bool	rdrflag;

	rdrflag = false;
	_lst = tknlst;
	cmd = NULL;
	while (_lst)
	{
		_tkn = _lst->content;
		if (_tkn->type == CMD)
			cmd = _add_cmd(_tkn, &rdrflag);
		else if (_tkn->type == ARG && !rdrflag)
			ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(_tkn), NULL));
		else if (_tkn->type != PIPE)
		{
			rdrflag = true;
			_lst = _add_redirection(_lst, cmd);
			continue ;
		}
		_lst = _lst->next;
	}
	_exec_pipeline();
}
