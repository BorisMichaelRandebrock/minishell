/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/19 19:04:25 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

#define RD_END 0
#define WR_END 1
#define BUFFER_64KB 65536	//TODO poner como variable entorno?

static char *_proc_exec(t_process *context)
{
	int		pipe_fd[2];
	char	buffer[BUFFER_64KB];

	char	**args = malloc(4 * sizeof(char *));
	args[0] = "/bin/bash";
	args[1] = "-c";
	args[2] = "compgen -b";
	args[3] = NULL;

	ft_memset(buffer, NUL_CH, sizeof(buffer));
	pipe(pipe_fd);
	context->_pid = fork(); //fork devuelve el pid
	if (context->_pid == 0)	// HIJO este codigo se ejecuta para el neuvo proceso...
	{
		close(pipe_fd[RD_END]);
		dup2(pipe_fd[WR_END], STDOUT_FILENO);
		close(pipe_fd[WR_END]);
		execve(args[0], args, NULL);
	}
	else	// PADRE, que es quien recibira el output...
	{
		wait(NULL);
		close(pipe_fd[WR_END]);
		ssize_t buff_sz = read(pipe_fd[RD_END], buffer, BUFFER_64KB);
		//TODO comprobar error y max buffer
		context->_output = malloc(buff_sz * sizeof(char)); //TODO liberar esto en destino
		//TODO guardas malloc...
		ft_strlcpy(context->_output, buffer, buff_sz);
		printf("%s\n", context->_output);
		close(pipe_fd[RD_END]);

	}
	return (context->_output);
}


//Free process object resources
static void _destructor(t_shell *shell)
{
	//TODO implement destroyer if needed
	shell->_is_running = false;
	if (shell->_parser)
		shell->_parser->destroy(shell->_parser);
	if (shell->_prompt)
		shell->_prompt->destroy(shell->_prompt);
	if (shell->_enviorment) 						//TODO armonizar parametros
		shell->_enviorment->destroy(shell->_enviorment);
	free(shell);
	//TODO llamar a todos los destructores...
}

//Signal handler hub
static void _sig_handler(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;

	//TODO implement action on signal recieved
}


static void _builtin_exec(t_command *command)
{
	(void)command;	//TODO implementar
}

//Create new process object
t_shell	*new_shell(char **env)
{
	t_shell	*new;
	struct sigaction _sig_action;

	new = malloc(sizeof(t_shell));
	if (!new)
		sh_exit(new, MEM_ERROR);
	_sig_action.__sigaction_u.__sa_sigaction = _sig_handler;	//TODO esta en en el stack?? SIGNAL!
	new->sig_action = _sig_action;
	new->_is_running = true;
	new->_enviorment = new_enviorment(new, env);
	new->_parser = new_parser(new);
	new->destroy = _destructor;
	new->proc_exec = _proc_exec;
	new->builtin_exec = _builtin_exec;
	sh_calloc(new,0);
	return (new);
}
