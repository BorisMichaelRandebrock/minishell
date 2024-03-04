/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:05 by brandebr          #+#    #+#             */
/*   Updated: 2024/03/04 18:00:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

//TODO return errors?
//TODO option -n
int	__echo(t_list *args, int fd)
{
	t_list	*_args;
	t_token	*tkn;

	_args = args;
	while (_args)
	{
		tkn = _args->content;
		write(fd, tkn->str, ft_strlen(tkn->str));
		if (_args->next)
			write(fd, " ", 1);
		_args = _args->next;
	}
	write(fd, "\0", 1);
	if (fd == STDOUT_FILENO)
		write(fd, "\n", 1);
	if (fd > SYS_FDS)
		close(fd);
	sh_exit(SUCCESS);
	return (SUCCESS);
}
