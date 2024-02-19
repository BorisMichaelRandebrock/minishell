/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/19 19:05:04 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

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
		shell->_parser->parse(shell);

		shell->destroy(shell);
	}
	return (SUCCESS);
}
