/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 15:44:23 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	_get_raw_prompt(t_shell *sh)
{
		sh->raw = readline("🐌 minishell> ");
		if (!sh->raw)
			sh_exit(NULL, MEM_ERROR);
		ft_lstadd_back(&sh->free_lst,ft_lstnew(sh->raw));
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
		printf("%s\n", sh->raw);
		break ;
	}
	sh_exit(NULL,SUCCESS);
	return (SUCCESS);
}
