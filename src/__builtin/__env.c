/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/24 17:21:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	__env(t_list *args)
{
	t_shell	*sh;
	size_t	i;

	(void)args;
	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		write(STDOUT_FILENO, sh->env[i], ft_strlen(sh->env[i]));
		if (sh->env[++i])
			write(STDOUT_FILENO, "\n", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
