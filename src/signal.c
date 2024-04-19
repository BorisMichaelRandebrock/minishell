/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:07:13 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/19 16:27:24 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <readline/history.h>
#include "minishell.h"

#define	ANSI_DEL_SCHAR "\033[D\033[P\033[D\033[P"


static void	_sh_ctrlc_handler(int signal)
{
	if (signal == SIGINT)
	{
		fflush(0);
	}
}

void	sh_ctrld_handler(void)
{
		write(1, ANSI_DEL_SCHAR, 13);
		write(1, "\n", 1);
		sh_freexit(EXIT_SUCCESS);
}

void	sh_init_handlers(void)
{
	signal(SIGINT, _sh_ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
}
