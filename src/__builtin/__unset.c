/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 13:21:56 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "minishell.h"
#define VAR_NAME	0
#define VALUE		1

static int	_var_syntax_check(char *var_name)
{
	if (!ft_isalpha(*var_name) && *var_name != '_')
	{
		write(STDOUT_FILENO, "unset: not a valid identifier\n", 31);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	__unset(t_list *args)
{
	t_list	*_args;
	t_token	*tkn;
	char	*_var;

	_args = args;
	if (!args)
	{
		write(STDOUT_FILENO, "unset: not enough arguments\n", 29);
		return (FAILURE);
	}
	else
	{
		while (_args)
		{
			tkn = _args->content;
			if (_var_syntax_check(tkn->str) == FAILURE)
				return (FAILURE);
			_var = sh_guard(ft_strjoin(tkn->str, "="), NULL);
			unset_evar(_var);
			_args = _args->next;
			sh_free(&_var);
		}
	}
	return (SUCCESS);
}
