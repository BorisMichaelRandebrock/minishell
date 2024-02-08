/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 14:50:00 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_arg
{
	char		*text;
	t_arg		*next;
}	t_arg;

typedef struct s_command	t_command;

typedef struct s_command
{
	char	*_name;
	t_arg	*_arg_lst;
	void	(*destroy)(t_command *command);
	void	(*consume_arg)(t_command *command);
}	t_command;

t_command	new_command(void);
t_arg		new_arg(void);

#endif
