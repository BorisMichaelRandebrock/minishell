/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:51:31 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 18:09:13 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	sh_store_stdio(void)
{
	t_shell	*sh;

	sh = get_shell();
	sh->_stdout = dup(STDOUT_FILENO);
	sh->_stdin = dup(STDIN_FILENO);
}

void	sh_restore_stdio(void)
{
	t_shell	*sh;

	sh = get_shell();
	dup2(sh->_stdin, STDIN_FILENO);
	dup2(sh->_stdout, STDOUT_FILENO);
}

void	sh_redirect_stdin(int fd)
{
	dup2(fd, STDIN_FILENO);
}

void	sh_redirect_stdout(int fd)
{
	dup2(fd, STDOUT_FILENO);
}
