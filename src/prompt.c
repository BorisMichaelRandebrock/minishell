/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/06 18:03:45 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

/*
	NOTAS PARA APRENDER:
		readline se ejecuta sobre el proceso padre, es solo una funcion
		readline reserva memoria que debe ser posteriormente liberada.

		history tambien se ejecuta sobre el proceso padre y no se pierde hasa el fin del proceso.
		history NO reserva memoria y es gestionado de forma automatica
*/

//Free process object resources
static void	_destructor(t_prompt *prompt)
{
	free(prompt->_input);
}

//Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	prompt->_input = readline("minishell> ");
	using_history();
	add_history(prompt->_input);
}

//Create new process object
t_prompt	new_prompt(void)
{
	t_prompt	new;

	new._input = NULL;
	new.destroy = _destructor;
	new.invoke = _invoker;
	return (new);
}
