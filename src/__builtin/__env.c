/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/06 21:23:02 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define SYS_FDS	2

//TODO //BUG el la ultima entrada impresa no tiene salto de linea!
int	__env(t_list *args, int fd)
{
	t_shell	*sh;
	size_t	i;

	(void)args;
	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		write(fd, sh->env[i], ft_strlen(sh->env[i]));
		if (sh->env[++i])
			write(fd, "\n", 1);
	}
	write(fd, "\n", 1);
	if (fd > SYS_FDS)
	{
		write(fd, "\0", 1);
		close(fd);
	}
	return (SUCCESS);
}
