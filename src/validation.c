/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:30 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 17:46:02 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/syslimits.h>
#include "minishell.h"

#define CMD_NOT_FOUND_ECODE	"127"
#define SYNTAX_ERROR_MSG	"Syntax error"
#define FILE_ERROR_MSG		"File error"
#define CMD_ERROR_MSG		"Command error"
#define OPERATORS			2

bool	sh_is_accesible(char *cmd_name)
{
	char	**splitted;
	int		i;
	char	buffer[BUF_1KB + NUL_SZ];

	if (access(cmd_name, F_OK) == SUCCESS)
		if (access(cmd_name, X_OK) != SUCCESS)
			return (false);
	return (true);
	ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
	splitted = sh_guard(ft_split(get_evar("PATH="), ':'), NULL);
	i = 0;
	while (splitted[i] && !sh_fexists(buffer))
	{
		ft_memset(buffer, '\0', BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, splitted[i++], BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, "/", BUF_1KB + NUL_SZ);
		ft_strlcat(buffer, cmd_name, BUF_1KB + NUL_SZ);
	}
	i = 0;
	while (splitted[i])
		sh_free(&splitted[i++]);
	sh_free(&splitted);
	if (access(buffer, X_OK) != SUCCESS)
		return (false);
	return (true);
}

static int	_validate_cmd(t_cmd *cmd)
{
	char	*cmd_name;

	if (cmd->tkn)
	{
		cmd_name = cmd->tkn->str;
		if (ft_strlen(cmd_name) > NAME_MAX)
		{
			errno = ENAMETOOLONG;
			sh_perror(SYNTAX_ERROR_MSG, false);
			return (FAILURE);
		}
		if (!is_builtin(cmd_name) && !sh_is_accesible(cmd_name))
		{
			set_evar("?=", CMD_NOT_FOUND_ECODE);
			sh_perror(CMD_ERROR_MSG, false);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	_validate_rdrin(t_list	*rdr_in)
{
	t_token	*tkn;

	while (rdr_in)
	{
		tkn = rdr_in->content;
		if (ft_strlen(tkn->str) > NAME_MAX)
		{
			errno = ENAMETOOLONG;
			sh_perror(SYNTAX_ERROR_MSG, false);
			return (FAILURE);
		}
		if (access(tkn->str, F_OK | R_OK) != SUCCESS)
		{
			sh_perror(FILE_ERROR_MSG, false);
			return (FAILURE);
		}
		rdr_in = rdr_in->next;
	}
	return (SUCCESS);
}

static int	_validate_rdrout(t_list	*rdr_out)
{
	char	*dir_name;
	t_token	*tkn;

	while (rdr_out)
	{
		tkn = rdr_out->content;
		if (ft_strlen(tkn->str) > NAME_MAX)
		{
			errno = ENAMETOOLONG;
			sh_perror(SYNTAX_ERROR_MSG, false);
			return (FAILURE);
		}
		dir_name = sh_get_dir_name(tkn->str);
		if (access(dir_name, W_OK) != SUCCESS
			|| (access(tkn->str, F_OK) == SUCCESS
				&& access(tkn->str, W_OK) != SUCCESS))
		{
			sh_perror(FILE_ERROR_MSG, false);
			sh_free(&dir_name);
			return (FAILURE);
		}
		sh_free(&dir_name);
		rdr_out = rdr_out->next;
	}
	return (SUCCESS);
}

// Validates commands
int	sh_cmd_validation(t_cmd *cmd)
{
	if (_validate_cmd(cmd) == FAILURE)
		return (FAILURE);
	if (_validate_rdrin(cmd->rdrs_in) == FAILURE)
		return (FAILURE);
	if (_validate_rdrout(cmd->rdrs_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
