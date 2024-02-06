/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:15:53 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/06 22:07:09 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "command.h"

//Free process object resources
static void	_destructor(t_command *command)	//TODO test
{
	t_arg	*arg;

	free(command->_name);
	while(command->_arg_lst)
	{
		arg = command->_arg_lst;
		free(arg->text);
		command->_arg_lst = command->_arg_lst->next;
		free(arg);
	}
	free(command);
}

//Consume an argument from a command object
static t_arg *_consume_arg(t_command *command) //TODO test
{
	t_arg	*arg;

	if (command->_arg_lst)
		arg = command->_arg_lst;
	else
		return (NULL);
	command->_arg_lst = command->_arg_lst->next;
	return (arg);
}

//Create new process object
t_command	new_command(void)
{
	t_command	new;

	new.consume_arg = _consume_arg;
	new.destroy = _destructor;
	return (new);
}
