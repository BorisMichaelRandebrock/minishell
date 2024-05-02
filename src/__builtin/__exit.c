/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:16:31 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 12:52:47 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

#define	NON_NUMERIC_ARG_ECODE	255

static bool	_contains_non_digit(char *str)
{
	while(*str)
	{
		if ((*str < '0' || *str > '9') && *str != '-')
			return (true);
		str++;
	}
	return (false);
}

int	__exit(t_list *args)
{
	t_shell	*sh;
	t_token	*tkn;
	int		exit_code;
	
	sh = get_shell();
	exit_code = 0;
	if (args)
		tkn = args->content;
	if (args && _contains_non_digit(tkn->str))
		exit_code = NON_NUMERIC_ARG_ECODE;
	else if (args && args->next)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (FAILURE);
	}
	else if (args)
		exit_code = ft_atoi(tkn->str);
	sh_restore_stdio();
	printf("exit\n");
	if (exit_code == NON_NUMERIC_ARG_ECODE)
		printf("minishell: exit: numeric argument required\n");
	sh_free_exit(exit_code);
	return (exit_code);
}
