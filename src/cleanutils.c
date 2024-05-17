/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:16:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/17 12:35:06 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "readline/history.h"
#include "minishell.h"

static void	_freeenv(void)
{
	t_shell	*sh;
	size_t	i;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		sh_free(&sh->env[i]);
		i++;
	}
	sh_free(&sh->env);
}

static void	_freeshell(void)
{
	t_shell	*sh;

	sh = get_shell();
	sh_free(&sh);
}

void	sh_free_reset(void)
{
	t_shell	*sh;

	sh = get_shell();
	sh_lfreeppln(sh->ppln);
	sh_lfreetkns(sh->tknlst);
}

//Clean exit from shell
void	sh_free_exit(int exit_code)
{
	t_shell	*sh;

	sh = get_shell();
	sh_free_reset();
	_freeenv();
	_freeshell();
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->trmcfgbackup);
	clear_history();
	exit(exit_code);
}
