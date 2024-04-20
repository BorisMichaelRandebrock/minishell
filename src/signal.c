/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:07:13 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/21 00:05:42 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

/* #define	ANSI_DEL_SCHAR "\033[D\033[P\033[D\033[P"
		write(1, ANSI_DEL_SCHAR, 13); */

static void	_sh_ctrlc_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sh_ctrld_handler(void)
{
		sh_freexit(EXIT_SUCCESS);
}

void	sh_init_handlers(void)
{
	signal(SIGINT, _sh_ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
}
