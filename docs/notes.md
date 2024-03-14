acerca de procesos...codigo antiguio:

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
