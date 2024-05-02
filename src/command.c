/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:49:46 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 18:05:12 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*_add_process(t_cmd *cmd, t_list *tknlst)
{
	t_token	*_tkn;

	_tkn = tknlst->content;
	if (!cmd->tkn)
	{
		cmd->tkn = _tkn;
		cmd->tkn->type = CMD;
		dequote_token(_tkn);
		tknlst = tknlst->next;
	}
	if (tknlst)
		_tkn = tknlst->content;
	while (tknlst && _tkn->type == ARG)
	{
		ft_lstadd_back(&cmd->args, sh_guard(ft_lstnew(_tkn), NULL));
		dequote_token(_tkn);
		tknlst = tknlst->next;
		if (tknlst)
			_tkn = tknlst->content;
	}
	return (tknlst);
}

static t_list	*_add_rdr(t_list *tknlst, t_list **rdrlst)
{
	t_token		*_tkn;
	t_tkntype	_type;

	_tkn = tknlst->content;
	_type = _tkn->type;
	tknlst = tknlst->next;
	if (tknlst)
	{
		_tkn = tknlst->content;
		if (_tkn->type == ARG)
			_tkn->type = _type;
	}
	if (_tkn->type != RDHDOC)
		dequote_token(_tkn);
	ft_lstadd_back(rdrlst, sh_guard(ft_lstnew(_tkn), NULL));
	return (tknlst->next);
}

static t_list	*_add_cmd(t_list *tknlst, t_list **ppln, t_cmd **cmd)
{
	*cmd = sh_calloc(1, sizeof(t_cmd));
	ft_lstadd_back(ppln, sh_guard(ft_lstnew(*cmd), NULL));
	if (tknlst)
		return (tknlst->next);
	return (NULL);
}

void	build_commands(t_list *tknlst, t_list **ppln)
{
	t_token	*tkn;
	t_cmd	*cmd;

	if (sh_syntax_check(tknlst) == FAILURE || !tknlst)
		return ;
	_add_cmd(tknlst, ppln, &cmd);
	while (tknlst)
	{
		tkn = tknlst->content;
		if (tkn->type == RDIN || tkn->type == RDHDOC)
			tknlst = _add_rdr(tknlst, &cmd->rdrs_in);
		else if (tkn->type == RDOUT || tkn->type == RDAPP)
			tknlst = _add_rdr(tknlst, &cmd->rdrs_out);
		else if (tkn->type == ARG)
			tknlst = _add_process(cmd, tknlst);
		else if (tkn->type == PIPE)
			tknlst = _add_cmd(tknlst, ppln, &cmd);
		else
			tknlst = tknlst->next;
	}
}
