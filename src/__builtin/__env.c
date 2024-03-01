/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:05 by brandebr          #+#    #+#             */
/*   Updated: 2024/03/01 18:52:45 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

//TODO return errors?
int	__env(t_list *args, int fd)
{
	t_shell	*sh;
	int		i;

	sh = get_shell();
	i = 0;
	(void)args;
	while (sh->env[i])
	{
		write(fd, sh->env[i], ft_strlen(sh->env[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	sh_exit(SUCCESS);
	return (SUCCESS);
}
