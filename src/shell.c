/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/01 18:13:03 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "process.h"
#include <unistd.h> //TODO check

static void _plaunch(t_process proc)
{
	(void)proc;
	/*
	//TODO fork shell/prompt?? then execute execve on new process

	#include <sys/wait.h>
	pid_t waitpid(pid_t pid, int *status, int options);

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
	(void)signal;
	(void)info;
	(void)context;

	//TODO implement action on signal recieved
}


t_shell	new_shell()
{
	t_shell	new;
	struct sigaction _sig_action;

	_sig_action.__sigaction_u.__sa_sigaction = _sig_handler;
	new.sig_action = _sig_action;
	new.m_destructor = _destructor;
	new.m_plaunch = _plaunch;
	//TODO register event on signal...
	//sigaction(SIGUSR1, &_sig_action, NULL);
	return (new);
}
