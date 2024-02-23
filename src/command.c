/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 17:44:41 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Creates a cmd sequence and stores it in shell parameters
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

