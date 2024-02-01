/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/01 18:14:45 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "prompt.h"
#include "shell.h"
#include "parser.h"

int	main(void)
{
	t_shell		shell;
	t_prompt	prompt;
	t_parser	parser;

	shell = new_shell();
	while (42) //TODO signal para salir del bucle, exit(), ctrl-c etc..
	{
		prompt = new_prompt();
		prompt.m_prompt();
		parser.m_parser(prompt.input);
		shell.m_plaunch(parser.parray);
		prompt.m_destructor();
		parser.m_destructor();
	}
	shell.m_destructor();
	return (EXIT_SUCCESS);
}
