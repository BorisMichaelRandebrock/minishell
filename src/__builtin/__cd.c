/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:26:03 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/15 16:57:27 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static int	_print_error(char *arg)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 32);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	return (FAILURE);
}

static void _chdir(char *arg)
{
	char	buf[BUFSIZ];

	getcwd(buf, BUFSIZ);
	if (chdir(arg) < 0)
		 _print_error(arg);
	set_evar("OLDPWD=", buf);
	set_evar("PWD=", getcwd(buf, BUFSIZ));
}

int	__cd(t_list *args, int fd)
{
	t_token	*tkn;

	(void)fd;
	if (!args)
		_chdir(get_evar("HOME="));
	else
	{
		tkn = args->content;
		if (!ft_strncmp(tkn->str, "-", 1))
		{
			if (!get_evar("OLDPWD="))
				_chdir(get_evar("HOME="));
			else
				_chdir(get_evar("OLDPWD="));
		}
		else if (!ft_strncmp(tkn->str, "~", 1))
			_chdir(get_evar("HOME="));
		else
			_chdir(tkn->str);
	}
	set_prompt();
	return (SUCCESS);
}
