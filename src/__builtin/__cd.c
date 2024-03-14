/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:26:03 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/14 12:16:45 by fmontser         ###   ########.fr       */
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

int	__cd(t_list *args, int fd)
{
	t_token	*tkn;
	char	buf[BUFSIZ];

	(void)fd;
	if (!args)
	{
		chdir("~");
		set_evar("PWD=", get_evar("HOME="));
		return (SUCCESS);
	}
	tkn = args->content;
	if (!ft_strncmp(tkn->str, "-", 1)) //TODO BUG no funciona dos veces..las rutas env no son relativas??
	{
		if (!get_evar("OLD_PWD="))
		{
			__pwd(NULL, fd);
			return (SUCCESS);
		}
	}
	getcwd(buf, BUFSIZ);
	if (chdir(tkn->str) < 0)
		return (_print_error(tkn->str));
	set_evar("OLD_PWD=", buf);
	set_evar("PWD=", getcwd(buf, BUFSIZ));
	return (SUCCESS);
}
