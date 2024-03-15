/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/15 12:55:02 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#define VAR_NAME	0
#define VALUE		1

int	__unset(t_list *args, int fd)
{
	t_list	*_args;
	t_token	*tkn;
	char	*_var;

	_args = args;
	if (!args)
	{
		write(fd, "unset: not enough arguments\n", 29);
		return (FAILURE);
	}
	else
	{
		while (_args)
		{
			tkn = _args->content;
			_var = sh_guard(ft_strjoin(tkn->str, "="), NULL);
			unset_evar(_var);
			_args = _args->next;
			free(_var);
		}
	}
	return (SUCCESS);
}
