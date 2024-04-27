/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:40:13 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 18:07:12 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "readline/history.h"
#include "readline/readline.h"

#define C_OPT "-c"


static bool	_c_opt_check(t_token *tkn, t_list **_args)
{
	if (!ft_strncmp(tkn->str, C_OPT, 3))
	{
		*_args = (*_args)->next;
		return (true);
	}
	return (false);
}

//TODO history segfault!!!
int	__history(t_list *args)
{
	t_list	*_args;
	bool	cflag;

	_args = args;
	cflag = _c_opt_check(_args->content, &_args);
	if (cflag)
	{
		clear_history();
		write(STDOUT_FILENO, "History file deleted.\n", 23);
		return (SUCCESS);
	}
	return (SUCCESS);
}
