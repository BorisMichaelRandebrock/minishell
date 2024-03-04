/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/04 16:56:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	sh = new_sh(sys_env);
	while (sh->is_running)
	{
		sh->input = sh_addfree(ft_strdup("echo hola | echo adios"));
		// sh->raw = sh_addfree(readline("🐌 minishell> "));
		parse(sh->input);
		typify(sh->tkn_lst);
		run_pipeline(sh->tkn_lst);

		sh->is_running =false;
	}
	sh_exit(SUCCESS);
}


//test env system

/* 		__env(NULL,1);
		set_evar("_", "/ola/que/ase");
		__env(NULL,1);
		set_evar("TVAR", "temporal var");
		__env(NULL,1); */
