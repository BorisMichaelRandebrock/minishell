/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/06 18:56:31 by fmontser         ###   ########.fr       */
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
	sh = new_sh(sys_env);
	while (sh->is_running)
	{
		sh->input = sh_addfree(ft_strdup("env | echo"));
		//sh->input = sh_addfree(readline("🐌 minishell> "));
		parse(sh->input);
		typify(sh->tkn_lst);

		//set_evar("__", "temporal var");
		run_pipeline(sh->tkn_lst);
		sh->is_running =false;
	}
	sh_exit(SUCCESS);
}


//test env system


