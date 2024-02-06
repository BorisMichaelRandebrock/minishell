/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/06 09:46:03 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO retirar

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"
#include "process.h"
#include "parser.h"
#include "libft.h"

#define RD_END 0
#define WR_END 1
#define FORKED_PROC 0
#define BUFFER_64KB 65536	//TODO poner como variable entorno?

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

static char *_proc_exec(t_process *context)
{
	(void)context;
	pid_t	new_pid;
	int		pipe_fd[2];
	char	buffer[BUFFER_64KB];
	char	*proc_out;
	char	*args[] = {"/bin/bash", "-c", "compgen -b", NULL}; //TODO integrar en t_process

	proc_out = NULL;
	ft_memset(buffer, '\0', sizeof(buffer));
	pipe(pipe_fd);
	new_pid = fork(); //fork devuelve el pid
	if (new_pid == FORKED_PROC)	// HIJO este codigo se ejecuta para el neuvo proceso...
	{
		close(pipe_fd[RD_END]);
		dup2(pipe_fd[WR_END], STDOUT_FILENO);
		close(pipe_fd[WR_END]);
		execve("/bin/bash", args, NULL);
	}
	else	// PADRE, que es quien recibira el output...
	{
		wait(NULL);
		close(pipe_fd[WR_END]);
		ssize_t buff_sz = read(pipe_fd[RD_END], buffer, BUFFER_64KB);
		//TODO comprobar error y max buffer
		proc_out = malloc(buff_sz * sizeof(char)); //TODO liberar esto en destino
		//TODO guardas malloc...
		ft_strlcpy(proc_out,buffer, buff_sz);
		printf("%s\n", proc_out);
		close(pipe_fd[RD_END]);

	}
	return (proc_out);
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

static void _get_builtins(t_parser *context)
{
	(void)context;	//TODO implementar
}

t_shell	new_shell()
{
	t_shell	new;
	struct sigaction _sig_action;

	_sig_action.__sigaction_u.__sa_sigaction = _sig_handler;
	new.sig_action = _sig_action;
	new.destroy = _destructor;
	new.proc_exec = _proc_exec;
	new.get_builtins = _get_builtins;
	return (new);
}
