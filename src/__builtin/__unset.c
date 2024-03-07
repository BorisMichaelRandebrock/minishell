/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/07 16:01:34 by fmontser         ###   ########.fr       */
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
			unset_evar(tkn->str);
			_args = _args->next;
		}
	}
	return (SUCCESS);
}
