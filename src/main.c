/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:19:28 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/05 16:34:04 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"
#include "prompt.h"
#include "parser.h"
#include <stdbool.h>


int	main(void)
{
	t_shell		shell;
	t_prompt	prompt;
	t_parser	parser;
	bool		continue_flag;

	shell = new_shell();
	continue_flag = true;
	while (continue_flag)	//TODO signal para salir del bucle, exit()...
	{
		prompt = new_prompt();
		prompt.invoke(&prompt);
		parser = new_parser();
		parser.parse(&prompt);
		prompt.destroy(&prompt);
	}
	shell.destroy();
	return (EXIT_SUCCESS);
}
