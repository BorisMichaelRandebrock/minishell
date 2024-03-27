/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:20:05 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 13:33:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libfm.h"
#include "libft.h"

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
			_var = fm_mshld_(ft_strjoin(tkn->str, "="), ex_mem);
			unset_evar(_var);
			_args = _args->next;
			free(_var);
		}
	}
	return (SUCCESS);
}
