/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:51:07 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/01 15:33:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
 # define SHELL_H

 # include <signal.h>

typedef struct s_shell
{
	struct sigaction	sig_action;
	void				(*sig_handler)();
	void				(*destructor)();
	void				(*pfork)();

}	t_shell;

t_shell	new_shell();

#endif
