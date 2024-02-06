/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:51:07 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/06 09:40:15 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <signal.h>
# include "prompt.h"
# include "parser.h"
# include "process.h"

typedef struct s_shell t_shell;

typedef struct s_shell
{
	struct sigaction	sig_action;
	void				(*destroy)(t_shell	*context);
	char				*(*proc_exec)(t_process *context);
	void				(*get_builtins)(t_parser *context);
}	t_shell;

t_shell	new_shell(void);

#endif
