/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:09:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 17:33:58 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "readline/readline.h"
#include "minishell.h"

#define SYNTAX_ERROR_MSG	"Syntax error"
#define FILE_ERROR_MSG		"File error"
#define CMD_ERROR_MSG		"Command error"
#define OPERATORS			2

// Validates syntax, NAME_MAX, Operators
int	sh_syntax_validation(t_list *tknlst)
{
	t_token	*tkn;
	t_token	*prev;

	prev = NULL;
	while (tknlst)
	{
		tkn = tknlst->content;
		if (ft_strlen(tkn->str) > NAME_MAX)
		{
			errno = ENAMETOOLONG;
			sh_perror(SYNTAX_ERROR_MSG, false);
			return (FAILURE);
		}
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

/* //TODO 42Minishell/::> cat -e src/__builtin/_cd.c
cat: src/__builtin/_cd.c: No such file or directory */

// Validates commands
int	sh_cmd_validation(t_cmd *cmd)
{
	char	*cmd_name;
	char	*dir_name;
	t_list	*_rdr_in;
	t_list	*_rdr_out;
	t_token	*tkn;

	// CMD
	cmd_name = cmd->tkn->str;
	if (!is_builtin(cmd_name) && !_is_executable(cmd_name))
	{
		sh_perror(CMD_ERROR_MSG, false);
		return (FAILURE);
	}

	//RDIN
	_rdr_in = cmd->rdrs_in;
	while (_rdr_in)
	{
		tkn = _rdr_in->content;
		if (access(tkn->str,  F_OK | R_OK) != SUCCESS)
		{
			sh_perror(FILE_ERROR_MSG, false);
			return (FAILURE);
		}
		_rdr_in = _rdr_in->next;
	}
	// RDOUT
	_rdr_out = cmd->rdrs_out;
	while (_rdr_out)
	{
		tkn = _rdr_out->content;
		dir_name = sh_get_dir_name(tkn->str);
		if (access(dir_name, W_OK) != SUCCESS 
			|| access(tkn->str, W_OK) != SUCCESS)
		{
			sh_perror(FILE_ERROR_MSG, false);
			sh_free(&dir_name);
			return (FAILURE);
		}
		sh_free(&dir_name);
		_rdr_out = _rdr_out->next;
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
