/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/02 13:32:39 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#define NAME	0
#define VALUE	1

static void	_free(char	**evar)
{
	if (evar)
	{
		sh_free(&evar[NAME]);
		sh_free(&evar[VALUE]);
		sh_free(&evar);
	}
}

static int	_print_error(char *evar)
{
	write(STDERR_FILENO, "export: not valid in this context: ", 36);
	write(STDERR_FILENO, evar, ft_strlen(evar));
	write(STDERR_FILENO, "\n", 1);
	return (FAILURE);
}

static int	_check_evar(int *eflag, char *evar, t_list **_args)
{
	if (!ft_strchr(evar, '='))
	{
		if (!*eflag)
			*eflag = _print_error(evar);
		*_args = (*_args)->next;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	__export(t_list *args, int fd)
{
	t_list	*_args;
	t_token	*tkn;
	int		eflag;
	char	**evar;

	eflag = SUCCESS;
	_args = args;
	if (!args)
		__env(NULL, fd);
	else
	{
		while (_args)
		{
			tkn = _args->content;
			if (_check_evar(&eflag, tkn->str, &_args))
				continue ;
			evar = ft_split(tkn->str, '=');
			evar[NAME] = sh_guard(ft_strjoin(evar[NAME], "="), evar[NAME]);
			set_evar(evar[NAME], evar[VALUE]);
			_args = _args->next;
			_free(evar);
		}
	}
	return (eflag);
}
