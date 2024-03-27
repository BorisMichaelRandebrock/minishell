/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:16:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/27 11:51:55 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libfm.h"
/*
void	sh_free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();

	//TODO free el resto de cosas...
	free(sh);
}

void	sh_free_env(void)
{
	t_shell	*sh;
	size_t	i;

	sh = get_shell();
	i = 0;
	while(sh->env[i])
	{
		free(sh->env[i]);
		i++;
	}
	free(sh->env);
}

//TODO estructurar...
void sh_free_iter(void)
{
	t_shell *sh;
	t_token *tkn;
	t_cmd	*cmd;
	t_list	*node;
	t_list	*subnode;
	t_list	*prev_node;

	sh = get_shell();

	// free tokens
	node = sh->tknlst;
	while(node)
	{
		tkn = node->content;
		free(tkn->str);
		free(tkn);
		prev_node = node;
		node = node->next;
		free(prev_node);
	}
	sh->tknlst = NULL;

	//free commands
	node = sh->pplnlst;
	while(node)
	{
		cmd = node->content;
		//free arglist
		subnode = cmd->args;
		while (subnode)
		{
			prev_node = subnode;
			subnode = subnode->next;
			free(prev_node);
		}
		subnode = cmd->rdrs;
		while (subnode)
		{
			prev_node = subnode;
			subnode = subnode->next;
			free(prev_node);
		}
		free(cmd);
		prev_node = node;
		node = node->next;
		free(prev_node);
	}
	sh->pplnlst = NULL;
}
*/
//Clean exit from shell
void	sh_freexit(int exit_code)
{
	t_shell	*sh;
	size_t	i;

	i = 0;
	sh = get_shell();
	fm_lstwipe(sh->exitlst);
	exit(exit_code);
}
