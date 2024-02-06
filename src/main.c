/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/06 09:41:07 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"
#include "prompt.h"
#include "parser.h"
#include <stdbool.h>


int	main(void)
{
	bool		continue_flag;
	t_shell		shell;
	t_parser	parser;
	//t_prompt	prompt;

	continue_flag = true;
	shell = new_shell();
	parser = new_parser();
	shell.proc_exec(NULL); //TODO test
/*
	while (continue_flag)	//TODO signal para salir del bucle, exit()...
	{
		prompt = new_prompt();
		prompt.invoke(&prompt);
	}
	shell.destroy(&shell); */
	return (EXIT_SUCCESS);
}
