/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/13 10:31:26 by fmontser         ###   ########.fr       */
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
	set_evar("HOME=", "olaquease");
	printf("%s\n", get_evar("HOME="));
	sh_freexit(SUCCESS);
	while (1)
	{
		sh->input = sh_guard(readline("🐌 minishell> "));
		parse(sh->input);
		typify(sh->tkn_lst);
		run_pipeline(sh->tkn_lst);
	}
	return (SUCCESS);
}


