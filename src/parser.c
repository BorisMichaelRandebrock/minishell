/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 14:24:57 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "parser.h"
#include "process.h"
#include "prompt.h"
#include "libft.h"
#include "defs.h"
#include "sterm.h"

//Free process object resources
static void	_destructor(t_parser *context)
{
	// TODO implement destroyer if needed
	free(context->_split); //TODO liberar recursivamente
}

/* static bool	_check_bad_args(char **_split)
{
	(void)_split;
	char	*_metachars;
	_metachars = "<>|$";
	return (false);
} */

//Parse user input via prompt object
static void	_parse_prompt(t_parser *context, t_prompt *prompt)
{
	t_sterm	list;
	//t_sterm	prev;
	int		i;

	context->_split = ft_split(prompt->_input, ' ');
	i = 0;
	list = new_sterm();
	list = (t_sterm){context->_split[i], list.get_type(context->_split[i]), NULL, NULL, list.get_type};
	i++;
	while(context->_split[i])
	{
		list.next = &(t_sterm){context->_split[i], list.get_type(context->_split[i]), NULL, &list, list.get_type};
		list = *list.next;
		i++;
	}

/* 	if(_check_bad_args(context->_split))
		printf("true\n"); */
}

//Create new process object
t_parser	new_parser(void)
{
	t_parser	new;

	new.destroy = _destructor;
	new.parse = _parse_prompt;
	return (new);
}
