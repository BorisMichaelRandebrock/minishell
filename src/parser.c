/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 16:59:25 by fmontser         ###   ########.fr       */
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
	int	i;

	i = 0;
	while(context->_split[i])
	{
		free(context->_split[i]); //TODO check leaks!
		i++;
	}
}

//Validates a correct input
/* static bool	_validate_input(t_sterm *term_list)
{
	//TODO @@@@@@@@@ validate with rules

	return (true);
} */

//Parse user input via prompt object
static void	_parse_prompt(t_parser *context, t_prompt *prompt)
{
	t_sterm	*head;
	int		i;

	context->_split = ft_split(prompt->_input, ' ');
	i = 0;
	head = new_sterm();
	head->text = context->_split[i];
	head->type = head->get_type(context->_split[i]);
	i++;
	while(context->_split[i])
	{
		head->next = new_sterm();
		head->next->prev = head;
		head->next->text = context->_split[i];
		head->next->type = head->get_type(context->_split[i]);
		head = head->next;
		i++;
	}
	while(i > 0)
	{
		if (head->type == TEXT && !head->prev)
			head->type = CMD;
		else if (head->type == TEXT && head->prev->type != TEXT) // Si es TEXT	Y	el previo no es TEXT	O	es NULL...
			head->type = CMD;
		else if (head->type == TEXT)
			head->type = ARG;
		if (head->prev)
			head = head->prev;
		i--;
	}





/* 	if(!_validate_input(context->_split))
		printf("false\n");	//TODO test borrar */
}

//Create new process object
t_parser	new_parser(void)
{
	t_parser	new;

	new.destroy = _destructor;
	new.parse = _parse_prompt;
	return (new);
}
