/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 19:56:54 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (!shell)
		shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		sh_perror(MEM_ERROR);
	return (shell);
}


int	main(int argc, char *argv[], char *env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_sh(env);
	while (sh->is_running)
	{
		sh->raw = sh_addfree(ft_strdup("'echo' |\"hola\">>'adios'"));
		// sh->raw = sh_addfree(readline("🐌 minishell> "));
		parse(sh->raw);
		while (sh->tkn_lst)
		{
			printf("%s\n", ((t_token *)sh->tkn_lst->content)->string);
			sh->tkn_lst = sh->tkn_lst->next;
		}
		break ;
		sh->raw = sh_addfree(ft_strdup("echo \"hola $PWD O_O\" | echo 'adios'"));
		//sh->raw = sh_addfree(readline("🐌 minishell> "));
		parse(sh->raw);
		sequence_cmd(sh, sh->tkn_lst);

		sh->is_running =false;
	}
	sh_exit(SUCCESS);
}

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
