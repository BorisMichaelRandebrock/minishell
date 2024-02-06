/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/06 22:09:56 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO retirar test

#include <stdlib.h>
#include "process.h"
#include "libft.h"

//Free process object resources
static void	_destructor(t_process *context)
{
	if (context->_ppath)
		free(context->_ppath);
	if (context->_pargs)
		free(context->_pargs);
	if (context->_penvs)
		free(context->_penvs);
	if (context->_status)
		free(context->_status);
	if (context->_output)
		free(context->_output);
}

//Set absolute path to binary
static void	_set_path(t_process *context, char *path)
{
	size_t	path_sz;

	path_sz = ft_strlen(path) + 1;
	context->_ppath = malloc(path_sz * sizeof(char));
	ft_strlcpy(context->_ppath, path, path_sz);
}

//Set process args ended with NULL arg.
static void	_set_args(t_process *context, char **args)
{
	//TODO implementar correctamente con t_command !!!
	size_t	args_count;
	size_t	arg_sz;
	int		i;
	char	**_args;

	args_count = 1;
	i = 0;
	while (args[i++])
		args_count++;
	_args = malloc(args_count * sizeof(char)); //TODO malloc guards
	i = 0;
	while (args[i])
	{
		arg_sz = ft_strlen(args[i]) + 1;
		_args[i] = malloc(arg_sz * sizeof(char)); //TODO malloc guard
		ft_strlcpy(_args[i], args[i], arg_sz);
		i++;
	}
	context->_pargs = _args;
}

//Set process enviorment variables ended with NULL arg. Format "ENV=value".
static void	_set_env(t_process *context, char **envs)
{
	//TODO implementar correctamente con t_command !!!
	size_t	envs_count;
	size_t	env_sz;
	int		i;
	char	**_envs;

	//TODO comprovar format de env "ENV=value"
	envs_count = 0;
	i = 0;
	while (envs[i++])
		envs_count++;
	_envs = malloc(envs_count * sizeof(char)); //TODO malloc guards
	i = 0;
	while (envs[i])
	{
		env_sz = ft_strlen(envs[i]) + 1;
		_envs[i] = malloc(env_sz * sizeof(char)); //TODO malloc guard
		ft_strlcpy(_envs[i], envs[i], env_sz);
		i++;
	}
	context->_pargs = _envs;
}

//Create new process object
t_process	new_process(void)
{
	t_process	new;

	new._status = NULL;
	new._ppath = NULL;
	new._penvs = NULL;
	new._output = NULL;
	new.set_path = _set_path;
	new.set_args = _set_args;
	new.set_env = _set_env;
	new.destroy = _destructor;
	return (new);
}
