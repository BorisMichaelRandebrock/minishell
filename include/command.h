/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/05 18:08:35 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdbool.h>

typedef enum e_argtype
{
	TEXT,
	SQUOTE,
	DQUOTE,
	DOLLAR,
	RD_OUT,
	APP_OUT,
	RD_IN,
	DL_IN,
	PIPE
}	t_argtype;

typedef struct s_arg t_arg;

typedef struct s_arg
{
	char		*text;
	bool		is_meta;
	t_argtype	type;
	t_arg		*next;
}	t_arg;

typedef struct s_command t_command;

typedef struct s_command
{
	char	*name;
	t_arg	*arg_lst;
	void	(*destroy)(t_command *command);
	void	(*consume_arg)(t_command *command);
}	t_command;

t_command	new_command(void);
t_arg		new_arg(void);

#endif
