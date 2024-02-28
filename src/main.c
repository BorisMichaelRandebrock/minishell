/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/28 19:59:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>


static void _testprint(void *tkn)
{
	t_token * _tkn = tkn;
	printf("%s\n", _tkn->str);
}

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_sh(sys_env);
	while (sh->is_running)
	{
		sh->raw = sh_addfree(ft_strdup(" \"'$X $X'\" "));
		// sh->raw = sh_addfree(readline("🐌 minishell> "));
		parse(sh->raw);
		typify(sh->tkn_lst);

		ft_lstiter(sh->tkn_lst, _testprint);
		//sequence_cmd(sh, sh->tkn_lst);
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
