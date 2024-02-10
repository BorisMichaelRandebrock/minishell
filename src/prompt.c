/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/10 18:08:22 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell.h"

//TODO borrar notas
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
	if (prompt)
	{
		free(prompt->_input);
		free(prompt);
	}
}

//Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	prompt->_input = readline("minishell> ");
	add_history(prompt->_input);
}

//Create new process object
t_prompt	*new_prompt(t_shell *shell)
{
	t_prompt	*new;

	new = malloc(sizeof(t_prompt));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	new->_input = NULL;	//TODO probar si usando calloc se peude evitar esto.
	new->_shell = shell;
	new->destroy = _destructor;
	new->invoke = _invoker;
	return (new);
}
