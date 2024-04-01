/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 13:42:00 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
		sh->tkn_lst = NULL;
		sh->ppln = NULL;
		sh->input = readline(get_evar("PROMPT="));
		add_history(sh->input);
		tokenizer(sh->input);
		run_pipeline(sh->tkn_lst);
		sh_lfreeppln(sh->ppln);
		sh_lfreetkns(sh->tkn_lst);
	}
	sh_freexit(SUCCESS);
	return (SUCCESS);
}
