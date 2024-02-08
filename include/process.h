/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 14:51:48 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <sys/types.h>

typedef struct s_process	t_process;

typedef struct s_process
{
	pid_t	_pid;
	int		*_status;
	char	*_ppath;
	char	**_pargs;
	char	**_penvs;
	char	*_output;
	//Free process object resources
	void	(*destroy)(t_process *context);
	//Set absolute path to binary
	void	(*set_path)(t_process *context, char *path);
	//Set process args ended with NULL arg.
	void	(*set_args)(t_process *context, char *args[]);
	//Set process enviorment variables ended with NULL arg. Format "ENV=value".
	void	(*set_env)(t_process *context, char *envs[]);
}	t_process;

//Create new process object
t_process	new_process(void);

#endif
