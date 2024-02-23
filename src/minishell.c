/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 18:13:13 by brandebr         ###   ########.fr       */
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
	}
	sh_exit(SUCCESS);
}
