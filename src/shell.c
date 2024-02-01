/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/01 15:52:08 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>

static void _plaunch()
{
	/*
	//TODO fork shell/prompt?? then execute execve on new process

	//int execve(const char *path, char *const argv[], char *const envp[]);

	path: Es la ruta del programa que se va a ejecutar.

	argv: Es un arreglo de cadenas de caracteres que representan los argumentos del programa.
	El último elemento del arreglo debe ser un puntero nulo (NULL) para indicar el final del arreglo.

	envp: Es un arreglo de cadenas de caracteres que representan las variables de entorno del programa.
	Al igual que con argv, el último elemento debe ser un puntero nulo.

	La función execve reemplaza la imagen de memoria del proceso actual con la del nuevo programa especificado
	por path. Si la llamada tiene éxito, el código de ejecución del programa especificado comenzará a ejecutarse,
	y el proceso actual se convertirá en el nuevo programa.

	*/
}

static void _destructor()
{
	//TODO implement destroyer if needed
}

static void _sig_handler(int signal, siginfo_t *info, void *context)
{
	//TODO implement action on signal recieved
}


t_shell	new_shell()
{
	t_shell	_shell;
	struct sigaction _sig_action;

	_sig_action.__sigaction_u.__sa_sigaction = _sig_handler;
	_shell.sig_action = _sig_action;
	_shell.sig_handler = _sig_handler;
	_shell.destructor = _destructor;
	//TODO register event on signal...
	//sigaction(SIGUSR1, &_sig_action, NULL);
	return (_shell);
}
