/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/13 12:28:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_shell(sys_env);
	while (1)
	{
		sh->tknlst = NULL;
		sh->ppln = NULL;

		sh->input = readline(get_evar("PROMPT="));
		//add_history(sh->input);
		tokenizer(sh->input);
		if (!sh->tknlst)
			continue ;
		build_commands(sh->tknlst, &sh->ppln);
		if (!sh_cmd_validation(sh->ppln, sh->tknlst))
			continue ;
		exec_pipeline(sh->ppln);
		sh_lfreeppln(sh->ppln);
		sh_lfreetkns(sh->tknlst);
	}
	sh_freexit(SUCCESS);
	return (SUCCESS);
}
