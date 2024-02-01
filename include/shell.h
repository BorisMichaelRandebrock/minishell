/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:51:07 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/01 16:55:09 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <signal.h>

typedef struct s_shell
{
	char				*input;
	struct sigaction	sig_action;
	void				(*sig_handler)();
	void				(*destructor)();
	void				(*pfork)();

}						t_shell;

t_shell					new_shell(void);

#endif
