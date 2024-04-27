/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:34:05 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/27 18:00:17 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define N_OPT	"-n"
#define SYS_FDS	2

static bool	_n_opt_check(t_token *tkn, t_list **_args)
{
	if (!ft_strncmp(tkn->str, N_OPT, 3))
	{
		*_args = (*_args)->next;
		return (true);
	}
	return (false);
}

int	__echo(t_list *args)
{
	t_list	*_args;
	t_token	*tkn;
	bool	nflag;

	if (!args)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	_args = args;
	nflag = _n_opt_check(_args->content, &_args);
	while (_args)
	{
		tkn = _args->content;
		write(STDOUT_FILENO, tkn->str, ft_strlen(tkn->str));
		if (_args->next && *((t_token *)_args->next->content)->str)
			write(STDOUT_FILENO, " ", 1);
		_args = _args->next;
	}
	if (!nflag)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
