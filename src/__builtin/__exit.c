/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:16:31 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/01 13:52:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

#define	NON_NUMERIC_ARG_ECODE 255

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
	t_token	*tkn;
	int		exit_code;
	
	exit_code = 0;
	tkn = args->content;
	printf("exit\n");
	if (_contains_non_digit(tkn->str))
	{
		printf("bash: exit: %s: numeric argument required", tkn->str);
		exit_code = NON_NUMERIC_ARG_ECODE;
	}
	else if (args)
	{
		exit_code = ft_atoi(tkn->str);
		if (args->next)
		{
			printf("minishell: exit: too many arguments");
			return (FAILURE);
		}
	}
	sh_free_exit(exit_code);
	return (exit_code);
}
