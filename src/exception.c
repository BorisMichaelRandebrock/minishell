/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:09:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 18:07:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <sys/syslimits.h>
#include "minishell.h"

#define CMD_NOT_FOUND_ECODE	"127"
#define SYNTAX_ERROR_MSG	"Syntax error"
#define FILE_ERROR_MSG		"File error"
#define CMD_ERROR_MSG		"Command error"
#define OPERATORS			2

// Checks syntax, NAME_MAX, Operators
int	sh_syntax_check(t_list *tknlst)
{
	t_token	*tkn;
	t_token	*prev;

	prev = NULL;
	while (tknlst)
	{
		tkn = tknlst->content;
		if ((!prev && tkn->type == PIPE)
			|| (!tknlst->next && tkn->type >= OPERATORS)
			|| (prev && prev->type >= OPERATORS && tkn->type >= OPERATORS))
		{
			errno = EINVAL;
			sh_perror(SYNTAX_ERROR_MSG, false);
			return (FAILURE);
		}
		prev = tkn;
		tknlst = tknlst->next;
	}
	return (SUCCESS);
}

// Prints system errors with optional clean exit
void	sh_perror(char *error_msg, bool exit)
{
	perror(error_msg);
	if (exit)
		sh_free_exit(FAILURE);
}
