/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 18:10:30 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "process.h"
#include "prompt.h"
#include <readline/readline.h>
#include <stdbool.h>

static void	_destructor(void)
{
	// TODO implement destroyer if needed
}

static bool	_check_args(t_prompt prompt)
{
	(void)prompt;
	//TODO implementar
	return (true);
}

static void	_parser(t_prompt prompt)
{
	_check_args(prompt);
	(void)prompt;
	//TODO implementar resultado a -->  parser.parray
}

t_parser	new_parser(void)
{
	t_parser	new;

	new.m_destructor = _destructor;
	new.m_parser = _parser;
	return (new);
}
