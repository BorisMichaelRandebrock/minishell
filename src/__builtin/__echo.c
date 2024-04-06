/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:05 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/06 21:22:57 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define N_OPT	"-n"
#define SYS_FDS	2

//TODO return errors?
static bool	_n_opt_check(t_token *tkn, t_list **_args)
{
	if (!ft_strncmp(tkn->str, N_OPT, 3))
	{
		*_args = (*_args)->next;
		return (true);
	}
	return (false);
}

int	__echo(t_list *args, int fd)
{
	t_list	*_args;
	t_token	*tkn;
	bool	nflag;

	_args = args;
	nflag = _n_opt_check(_args->content, &_args);
	while (_args)
	{
		tkn = _args->content;
		write(fd, tkn->str, ft_strlen(tkn->str));
		if (_args->next && *((t_token *)_args->next->content)->str )
			write(fd, " ", 1);
		_args = _args->next;
	}
	if (!nflag)
		write(fd, "\n", 1);
	if (fd > SYS_FDS)
		close(fd);
	return (SUCCESS);
}
