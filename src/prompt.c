/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 17:50:35 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include <readline/readline.h>

static void	_destructor(void)
{
	// TODO implement destroyer if needed
}
static void	_prompt(void)
{
	// TODO implement prompt when needed
}

t_prompt	new_prompt(void)
{
	t_prompt	new;

	new.input = NULL;
	new.m_destructor = _destructor;
	new.m_prompt = _prompt;
	return (new);
}
