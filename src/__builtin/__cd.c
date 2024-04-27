/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:26:03 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 20:22:54 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

static int	_print_error(char *arg)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 32);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	return (FAILURE);
}

static void	_chdir(char *arg)
{
	char	buf[BUF_1KB];

	getcwd(buf, BUF_1KB);
	if (chdir(arg) < 0)
		_print_error(arg);
	set_evar("OLDPWD=", buf);
	set_evar("PWD=", getcwd(buf, BUF_1KB));
}

int	__cd(t_list *args)
{
	t_token	*tkn;

	if (!args)
		_chdir(get_evar("HOME="));
	else
	{
		tkn = args->content;
		if (!ft_strncmp(tkn->str, "-", 2))
		{
			if (!get_evar("OLDPWD="))
				_chdir(get_evar("HOME="));
			else
			{
				printf("%s\n", get_evar("OLDPWD="));
				_chdir(get_evar("OLDPWD="));
			}
		}
		else if (!ft_strncmp(tkn->str, "~", 2))
			_chdir(get_evar("HOME="));
		else
			_chdir(tkn->str);
	}
	set_prompt();
	return (SUCCESS);
}
