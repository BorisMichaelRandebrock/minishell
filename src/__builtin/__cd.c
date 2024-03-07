/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:26:03 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/07 18:15:54 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static bool	_print_error(char *arg)
{
	write(STDERR_FILENO, "cd: no such file or directory: ", 32);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	return (true);
}

int	__cd(t_list *args, int fd)
{
	t_list			*_args;
	t_token			*tkn;
	char			buf[BUFSIZ];
	(void)fd;

	if(!args)
	{
		chdir("~");
		set_evar("PWD", get_evar("HOME"));
		return (SUCCESS);
	}
	_args = args;
	tkn = _args->content;
	set_evar("OLD_PWD", getcwd(buf, BUFSIZ));


	//TODO @@@@@@ si no encuetra el dir...muestra error
	int hula = chdir(tkn->str) > 0;

	if (hula)
		_print_error(tkn->str);
	set_evar("PWD", getcwd(buf, BUFSIZ));
	return (SUCCESS);
}
