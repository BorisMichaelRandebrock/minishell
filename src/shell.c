/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/13 10:24:25 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

#define DFLT_ENV_SZ 5

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (!shell)
		shell = sh_guard(ft_calloc(1, sizeof(t_shell)));
	return (shell);
}

t_shell	*new_sh(char **sys_env)
{
	t_shell	*sh;

	sh = get_shell();
	sh->env = new_env(sys_env, &sh->env_sz);
	return (sh);
}
