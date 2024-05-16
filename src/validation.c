/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:25:30 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/16 15:43:13 by fmontser         ###   ########.fr       */
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

	if (sh_check_current_dir(cmd_name))
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

bool	validate_cmd(t_cmd *cmd)
{
	char	*cmd_name;

	if (cmd->tkn)
	{
		cmd_name = cmd->tkn->str;
		if (ft_strlen(cmd_name) > NAME_MAX)
		{
			errno = ENAMETOOLONG;
			sh_perror(SYNTAX_ERROR_MSG, false);
			return (false);
		}
		if (!is_builtin(cmd) && !sh_is_accesible(cmd_name))
		{
			set_evar("?=", CMD_NOT_FOUND_ECODE);
			sh_perror(CMD_ERROR_MSG, false);
			return (false);
		}
	}
	return (true);
}

bool	validate_rdrin(t_token	*_rdr)
{
	if (ft_strlen(_rdr->str) > NAME_MAX)
	{
		errno = ENAMETOOLONG;
		sh_perror(SYNTAX_ERROR_MSG, false);
		return (false);
	}
	if (_rdr->type != RDHDOC && access(_rdr->str, F_OK | R_OK) != SUCCESS)
	{
		sh_perror(FILE_ERROR_MSG, false);
		set_evar("?=", "1");
		return (false);
	}
	return (true);
}

bool	validate_rdrout(t_token	*_rdr)
{
	char	*dir_name;

	if (ft_strlen(_rdr->str) > NAME_MAX)
	{
		errno = ENAMETOOLONG;
		sh_perror(SYNTAX_ERROR_MSG, false);
		return (false);
	}
	dir_name = sh_get_dir_name(_rdr->str);
	if (access(dir_name, W_OK) != SUCCESS || (access(_rdr->str, F_OK)
			== SUCCESS && access(_rdr->str, W_OK) != SUCCESS))
	{
		sh_perror(FILE_ERROR_MSG, false);
		set_evar("?=", "1");
		sh_free(&dir_name);
		return (false);
	}
	sh_free(&dir_name);
	return (true);
}
