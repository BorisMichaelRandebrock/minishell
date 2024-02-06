/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:15:53 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/05 18:46:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "command.h"

static void	_destructor(t_command *command)	//TODO test
{
	t_arg	*arg;

	free(command->name);
	while(command->arg_lst)
	{
		arg = command->arg_lst;
		free(arg->text);
		command->arg_lst = command->arg_lst->next;
		free(arg);
	}
	free(command);
}

static t_arg *_consume_arg(t_command *command) //TODO test
{
	t_arg	*arg;

	if (command->arg_lst)
		arg = command->arg_lst;
	else
		return (NULL);
	command->arg_lst = command->arg_lst->next;
	return (arg);
}


t_command	new_command(void)
{
	t_command	new;

	new.consume_arg = _consume_arg;
	new.destroy = _destructor;
	return (new);
}
