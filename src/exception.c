/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:09:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 15:06:44 by fmontser         ###   ########.fr       */
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
#define CMD_ERROR_MSG		"Command error"
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







// Check if executable exist and has permision
static bool	_is_executable(char *cmd_name)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1KB + NUL_SZ];

	if (sh_fexists(cmd_name))
		return (SUCCESS);
	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i] && !sh_fexists(buffer))
	{
		ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, splitted[i], BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, "/", BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, cmd_name, BUF_1KB + NUL_SZ);
		i++;
	}
	i = 0;
	while (splitted[i])
		sh_free(&splitted[i++]);
	sh_free(&splitted);
	if (access(buffer, F_OK | X_OK) != SUCCESS)
		return (false);
	return (true);
}

// Validates commands
int	sh_cmd_validation(t_cmd *cmd)
{
	char	*cmd_name;

	cmd_name = cmd->tkn->str;
	if (!is_builtin(cmd_name) && !_is_executable(cmd_name))
	{
		sh_perror(CMD_ERROR_MSG, false);
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
