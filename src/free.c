/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:16:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/21 18:06:21 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>


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
	node = sh->tkn_lst;
	while(node)
	{
		tkn = node->content;
		free(tkn->str);
		free(tkn);
		prev_node = node;
		node = node->next;
		free(prev_node);
	}
	sh->tkn_lst = NULL;

	//free commands
	node = sh->ppln;
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
	sh->ppln = NULL;
}

//Clean exit from shell
void	sh_freexit(int exit_code)
{
	t_shell	*sh;
	size_t	i;

	i = 0;
	sh = get_shell();
	sh_free_iter();
	sh_free_env();
	sh_free_shell();
	exit(exit_code);
}
