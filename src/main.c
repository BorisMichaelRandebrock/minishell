/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/29 17:35:46 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>


/* static void _testprint(void *cmd)
{
	t_cmd * _cmd = cmd;

	t_token *_tkn;
	_tkn = _cmd->args->content;
	printf("%s %s\n", _cmd->cmd->str, _tkn->str);
} */

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_sh(sys_env);
	while (sh->is_running)
	{
		sh->input = sh_addfree(ft_strdup("ECHO hola > file1 | CAT -e > file2"));
		// sh->raw = sh_addfree(readline("🐌 minishell> "));
		parse(sh->input);
		typify(sh->tkn_lst);
		get_pipeline(sh->tkn_lst);
		exec_pipeline(sh->ppln);

		//ft_lstiter(sh->ppln, _testprint);
		//sort_sequence(sh->cmd_lst);
		sh->is_running =false;
	}
	sh_exit(SUCCESS);
}

/* TEST token list */
/*
	while (sh->tkn_lst)
	{
		printf("%s\n", ((t_token *)sh->tkn_lst->content)->string);
		sh->tkn_lst = sh->tkn_lst->next;
	}
	break ;
 */


/*TEST cmd list */
/* 		while (sh->cmd_lst)
		{
			t_cmd	*scmd = (t_cmd *)sh->cmd_lst->content;
			t_list	*alist = (t_list *)scmd->args;

			printf("%s -", scmd->name->string);
			while (alist)
			{
				printf(" %s", ((t_token *)alist->content)->string);
				alist = alist->next;
			}
			printf("\n");
			sh->cmd_lst = sh->cmd_lst->next;
		} */
