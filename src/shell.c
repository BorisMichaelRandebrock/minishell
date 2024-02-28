/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/28 20:05:10 by fmontser         ###   ########.fr       */
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

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (!shell)
	{
		shell = ft_calloc(1, sizeof(t_shell));
		if (!shell)
			sh_perror(MEM_ERROR);
	}
	return (shell);
}

//Create new process object
t_shell	*new_sh(char **sys_env)
{
	t_shell	*sh;

	sh = get_shell();
	sh->is_running = true;
	sh->env = new_env(sys_env);
	return (sh);
}

/* static char *_proc_exec(t_process *context)
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
} */
