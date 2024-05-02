/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 16:15:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define NUL_SZ	1
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
	write(STDERR_FILENO, "export: invalid argument ", 26);
	write(STDERR_FILENO, evar, ft_strlen(evar));
	write(STDERR_FILENO, "\n", 1);
	return (FAILURE);
}

static int	_check_evar(int *exit_status, char *evar)
{
	if (!ft_strchr(evar, '=') || (!ft_isalpha(*evar) && *evar != '_'))
	{
		if (*exit_status == 0)
			_print_error(evar);
		*exit_status = FAILURE;
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	_push(t_token *tkn)
{
	char	**evar;

	evar = ft_split(tkn->str, '=');
	evar[NAME] = sh_guard(ft_strjoin(evar[NAME], "="), evar[NAME]);
	set_evar(evar[NAME], evar[VALUE]);
	_free(evar);
}

int	__export(t_list *args)
{
	t_list	*_args;
	t_token	*tkn;
	int		exit_status;

	exit_status = 0;
	_args = args;
	if (!args)
		__env(NULL);
	else
	{
		while (_args)
		{
			tkn = _args->content;
			if (_check_evar(&exit_status, tkn->str))
			{
				_args = _args->next;
				continue ;
			}
			_push(tkn);
			_args = _args->next;
		}
	}
	return (exit_status);
}
