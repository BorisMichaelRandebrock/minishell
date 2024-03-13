/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/13 14:36:56 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

//TODO estructurar...
static void _free_iteration(void)
{
	t_shell *sh;
	t_token *tkn;
	t_list	*node;
	t_list	*prev_node;

	// free tokens
	sh = get_shell();
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
}

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_shell(sys_env);
	while (1)
	{
		sh->input = sh_guard(readline("🐌 minishell> "), NULL);
		tokenizer(sh->input, sh->tkn_lst);
		//run_pipeline(sh->tkn_lst);
		_free_iteration();
		sh_freexit(0);
	}
	return (SUCCESS);
}


