/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/07 19:21:48 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO for tests

#include <stdbool.h>
#include <stdlib.h>
#include "shell.h"
#include "prompt.h"
#include "parser.h"
#include "process.h"



int	main(void)
{
	bool		continue_flag;
	t_shell		shell;
	t_parser	parser;
	t_prompt	prompt;

	continue_flag = true;
	shell = new_shell();
	parser = new_parser();


	while (continue_flag)	//TODO signal para salir del bucle, exit()...
	{
		prompt = new_prompt();
		prompt.invoke(&prompt);
		parser.parse(&parser, &prompt);
	}
	shell.destroy(&shell);
	return (EXIT_SUCCESS);
}
