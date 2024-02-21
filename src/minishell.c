/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/21 13:19:04 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

t_shell	*get_shell()
{
	static	t_shell *shell = NULL;

	if (!shell)
		shell = ft_calloc(1, sizeof(t_shell));
		if (!shell)
			sh_perror(MEM_ERROR);
	return (shell);
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	t_shell	*sh;

	t_list	*clear_lst;

	sh = new_sh(env);
 	while(sh->is_running)
	{
		//sh->raw = sh_addfree(ft_strdup("   'echo'   \"hola   \"'adios'''\"\"  '  \"  s "));
		sh->raw = sh_addfree(readline("🐌 minishell> "));
		parse(sh->raw);


		clear_lst = sh->tkn_lst;
		while (sh->tkn_lst)
		{
		printf("%s  -  %i\n", ((t_token *)sh->tkn_lst->content)->string, ((t_token *)sh->tkn_lst->content)->type);
		sh->tkn_lst = sh->tkn_lst->next;
		}
		ft_lstclear(&clear_lst, free);
		//break ;
	}
	sh_exit(SUCCESS);
}
