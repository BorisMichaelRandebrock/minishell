/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/15 20:57:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	cleanexit(t_shell *shell, int error_code)
{
	if (error_code == MEM_ERROR)
		printf("Memory error, exiting...");
	if (shell)
		shell->destroy(shell);
	exit(FAILURE);
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell	*shell;
	(void)argc;
	(void)argv;

	shell = new_shell(env);
	while (shell->_is_running)
	{
		shell->_prompt = new_prompt(shell);
		shell->_prompt->invoke(shell->_prompt);
		//shell->_parser->parse(shell->_prompt);

		shell->destroy(shell);
	}
	return (SUCCESS);
}

/*

_=/usr/bin/make				ultimo proceso ejecutado (opcional)
?=0							ultimo codigo de salida recibido
PATH=/bin:/usr/local/bin	Rutas del PATH
PWD=/Users/~/minishell		Directorio actual (.)
OLDPWD=/Users/~				Directorio anterior (..)
TMPDIR=						Directorio temporal (opcional)

 */
