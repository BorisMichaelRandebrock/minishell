/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:09:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 14:25:46 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "readline/readline.h"
#include "minishell.h"

#define SYNTAX_ERROR_MSG	"Operator syntax error"
#define FILE_ERROR_MSG		"File error"
#define OPERATORS			2

// Validates operator syntax
int	sh_syntax_validation(t_list *tknlst)
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

//TODO excepcion, si un redir no tiene argumento o
// 		el argumento no es valido es un error
//TODO @@@@@@@@@@@@ validar comando y rdin files antes!!!!

// Validates commands and input redirection before execution

int	sh_cmd_validation(t_cmd *cmd)
{
	if (access(cmd->tkn->str, F_OK | X_OK) != SUCCESS)
	{
		sh_perror(FILE_ERROR_MSG, false);
		return (FAILURE);
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
