/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/07 19:22:32 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "parser.h"
#include "process.h"
#include "prompt.h"
#include "libft.h"
#include "defs.h"

//Free process object resources
static void	_destructor(t_parser *context)
{
	// TODO implement destroyer if needed
	free(context->_split);
}

static bool	_check_bad_args(char **_split)
{
	char *	_metachars;

	_metachars = "<>|$";
	(void)_metachars;
	(void)_split;
	return (false);
}

//Parse user input via prompt object
static void	_parse_prompt(t_parser *context, t_prompt *prompt)
{
	context->_split = ft_split(prompt->_input, ' ');
	if(_check_bad_args(context->_split))
		printf("true\n");

}

//Create new process object
t_parser	new_parser(void)
{
	t_parser	new;

	new.destroy = _destructor;
	new.parse = _parse_prompt;
	return (new);
}
