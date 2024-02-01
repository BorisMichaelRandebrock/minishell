/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 17:53:18 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static void	_destructor(void)
{
	// TODO implement destroyer if needed
}

static void	_process(void)
{
	// TODO implement process when needed
}

t_process	new_process(void)
{
	t_process	new;

	new.m_destructor = _destructor;
	new.m_process =  _process;
	return (new);
}
