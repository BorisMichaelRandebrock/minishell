/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 21:04:26 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	_get_raw_prompt(t_shell *sh)
{
	sh->raw = ft_strdup("     echo \"hola   \"    'adios  ' aqui' alla  'otro");
	//sh->raw = readline("🐌 minishell> ");
	if (!sh->raw)
		sh_exit(NULL);
	while (ft_is_whspc(*sh->raw)) //TODO Quitar tim
		sh->raw++;
	ft_lstadd_back(&sh->free_cnt,ft_lstnew(sh->raw));
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	t_shell	*sh;

	sh = new_shell(env);
	while(sh->is_running)
	{
		_get_raw_prompt(sh);

		parse(sh, sh->raw);
		break ;
	}
	while (sh->tkn_lst)
	{
		printf("%s\n", ((t_token *)sh->tkn_lst->content)->string );
		sh->tkn_lst = sh->tkn_lst->next;
	}

	sh_exit(NULL);
	return (SUCCESS);
}
