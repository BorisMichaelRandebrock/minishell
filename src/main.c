/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/24 19:17:33 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "readline/history.h"
#include "readline/readline.h"
#include "minishell.h"

//TODO @@@@@@ continuar aqui, mutear
static void _fd_arg_guard(void)
{
 	char buffer[1024];
	int _stdin = dup(STDIN_FILENO);
	
	ft_memset(buffer, '\0', 1024);
	close(STDIN_FILENO);
	while (read(0, buffer, 1024) > 0)
		ft_memset(buffer, '\0', 1024);
	dup2(_stdin, 0);
	rl_replace_line("", 0);
}

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	(void)argc;
	(void)argv;
	_fd_arg_guard();
	sh = new_shell(sys_env);
	while (1)
	{
		sh->tknlst = NULL;
		sh->ppln = NULL;
		sh->input = readline(get_evar("PROMPT="));
		add_history(sh->input);
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
