/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/14 12:22:00 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#define VAR_NAME	0
#define VALUE		1

static void	_free(char	**evar)
{
	if (evar)
	{
		free(evar[VAR_NAME]);
		free(evar[VALUE]);
		free(evar);
	}
}

static bool	_print_error(char *evar)
{
	write(STDERR_FILENO, "export: not valid in this context: ", 36);
	write(STDERR_FILENO, evar, ft_strlen(evar));
	write(STDERR_FILENO, "\n", 1);
	return (true);
}

static bool	_check_evar(bool *eflag, char *evar, t_list **_args)
{
	if (!ft_strchr(evar, '='))
	{
		if (!*eflag)
			*eflag = _print_error(evar);
		*_args = (*_args)->next;
		return (true);
	}
	return (false);
}
//TODO BUG! no aplica el '=' a la nueva variable
//TODO los nombres de variables deben ser en MAYUSCULAS
int	__export(t_list *args, int fd)
{
	t_list	*_args;
	t_token	*tkn;
	bool	eflag;
	char	**evar;

	eflag = false;
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
			set_evar(evar[VAR_NAME], evar[VALUE]);
			_args = _args->next;
			_free(evar);
		}
	}
	if (eflag)
		return (FAILURE);
	return (SUCCESS);
}
