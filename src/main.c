/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/07 16:48:47 by fmontser         ###   ########.fr       */
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

/* 	while (sys_env)
	{
		printf("%s\n", *sys_env);
		sys_env++;
	} */

	sh = new_sh(sys_env);
	while (sh->is_running)
	{
		//sh->input = sh_addfree(ft_strdup("env"));
		sh->input = sh_addfree(readline("🐌 minishell> "));
		parse(sh->input);
		typify(sh->tkn_lst);
		run_pipeline(sh->tkn_lst);
		//sh->is_running = false;
	}
	sh_exit(SUCCESS);
}


