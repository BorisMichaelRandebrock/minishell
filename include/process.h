/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 17:49:39 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
#define PROCESS_H

typedef struct s_process
{
	char	*ppath;
	char**	pargs;
	char**	penv;
	void	(*m_destructor)();
	void	(*m_process)();
} t_process;

t_process new_process(void);

#endif
