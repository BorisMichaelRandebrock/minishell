/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 17:30:54 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sequence_cmd(t_shell *sh, t_list *tkn_lst)
{
	t_token	*tkn;
	t_cmd	*cmd;

	cmd = sh_calloc(1, sizeof(t_cmd));
	while(tkn_lst)
	{
		tkn = tkn_lst->content;
		if (tkn->type == CMD)
			cmd->name = tkn;
		else if (tkn->type == ARG)
			ft_lstadd_back(&cmd->args, sh_addfree(ft_lstnew(tkn)));
		else if (tkn->type == OP)
		{
			ft_lstadd_back(&sh->cmd_lst, sh_addfree(ft_lstnew(cmd)));
			cmd = sh_calloc(1, sizeof(t_cmd));
			cmd->name = tkn;
			ft_lstadd_back(&sh->cmd_lst, sh_addfree(ft_lstnew(cmd)));
			if (tkn_lst->next)
				sequence_cmd(sh, tkn_lst->next);
			return ;
		}
		tkn_lst = tkn_lst->next;
	}
	ft_lstadd_back(&sh->cmd_lst, sh_addfree(ft_lstnew(cmd)));
}
/*
void	sequence_cmd(t_list	*tkn_lst)
{
	t_shell	*sh;
	t_token	*tkn;
	t_cmd	*cmd;
	t_list	*tmp;

	sh = get_shell();
	cmd = sh_calloc(1, sizeof(t_cmd));
	tkn = tkn_lst->content;
	if (tkn_lst && tkn->type == OP)
	{
		cmd->cmd = tkn;
		tmp = sh_addfree(ft_lstnew(cmd));
		if (!sh->cmd_lst)
			sh->cmd_lst = tmp;
		else
			ft_lstadd_back(&sh->cmd_lst, tmp);
		if (tkn_lst->next)
			sequence_cmd(tkn_lst->next);
		return ;
	}
	while(tkn_lst)
	{
		tkn = tkn_lst->content;
		if (tkn->type == CMD)
			cmd->cmd = tkn;
		else if (tkn->type == ARG)
		{
			tmp = sh_addfree(ft_lstnew(tkn));
			if (!cmd->args)
				cmd->args = tmp;
			else
				ft_lstadd_back(&cmd->args, tmp);
		}
		else if (tkn->type == OP)
				//TODO que pasa?
		tkn_lst = tkn_lst->next;
	}
	if (tkn_lst)
		sequence_cmd(tkn_lst->next);
}

 */
