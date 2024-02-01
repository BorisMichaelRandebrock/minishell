/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 16:52:15 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include <readline/readline.h>
#include <stdio.h>

static void	_destructor(void)
{
	// TODO implement destroyer if needed
}
static void	_pronpt(void)
{
	// TODO implement prompt when needed
}

t_prompt	new_prompt(void)
{
	t_prompt	_prompt;

	_prompt.input = NULL;
	_prompt.destructor = _destructor;
	_prompt.prompt = _pronpt;
	return (_prompt);
}
