/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/05 16:54:08 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
/*
	NOTAS PARA APRENDER:
		readline se ejecuta sobre el proceso padre, es solo una funcion
		readline reserva memoria que debe ser posteriormente liberada.

		history tambien se ejecuta sobre el proceso padre y no se pierde hasa el fin del proceso.
		history NO reserva memoria y es gestionado de forma automatica
*/

static void	_destructor(t_prompt *prompt)
{
	free(prompt->_input);
}
static void	_invoker(t_prompt *prompt)
{
	prompt->_input = readline("minishell> ");

	using_history();
	add_history(prompt->_input);
}

t_prompt	new_prompt(void)
{
	t_prompt	new;

	new._input = NULL;
	new.destroy = _destructor;
	new.invoke = _invoker;
	return (new);
}