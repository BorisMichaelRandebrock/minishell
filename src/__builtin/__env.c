/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 14:12:12 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "fm_string.h"

int	__env(t_list *args, int fd)
{
	t_shell	*sh;
	size_t	i;

	(void)args;
	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		write(fd, sh->env[i], fm_strlen(sh->env[i]));
		if (sh->env[++i])
			write(fd, "\n", 1);
	}
	if (fd == STDOUT_FILENO)
		write(fd, "\n", 1);
	if (fd > SYS_FDS)
	{
		write(fd, "\0", 1);
		close(fd);
	}
	return (SUCCESS);
}
