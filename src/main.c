/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/19 14:30:20 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

//TODO estructurar...

void free_iteration(void)
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
		free(cmd);
		prev_node = node;
		node = node->next;
		free(prev_node);
	}
	sh->ppln = NULL;
}

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_shell(sys_env);
	while (1)
	{
		sh->input = sh_guard(readline(get_evar("PROMPT=")), NULL);
		add_history(sh->input);
		tokenizer(sh->input);
		run_pipeline(sh->tkn_lst);
		free_iteration();
	}
	sh_freexit(SUCCESS);
	return (SUCCESS);
}
