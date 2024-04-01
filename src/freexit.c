/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freexit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:16:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 13:27:32 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

//Clean exit from shell
void	sh_freexit(int exit_code)
{
	t_shell	*sh;
	size_t	i;

	i = 0;
	sh = get_shell();
	_freeenv();
	_freeshell();
	exit(exit_code);
}
