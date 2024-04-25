/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/25 20:48:25 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include <fcntl.h>
#include "readline/history.h"
#include "readline/readline.h"
#include "minishell.h"

static void _handle_args(int argc, char *argv[])
{
	int		tty_fd;

	(void)argc;
	(void)argv;
	tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDIN_FILENO);
	close(tty_fd);
}

int	main(int argc, char *argv[], char *sys_env[])
{
	t_shell	*sh;

	_handle_args(argc, argv);
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
