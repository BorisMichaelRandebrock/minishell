/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:07:13 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/17 12:48:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "readline/readline.h"
#include "minishell.h"

static void	_sh_ctrlc_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		set_evar("?=", "1");
	}
}

void	sh_ctrld_handler(void)
{
	sh_free_exit(EXIT_SUCCESS);
}

void	sh_init_handlers(void)
{
	signal(SIGINT, _sh_ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
}
