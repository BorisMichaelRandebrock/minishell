/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/08 18:29:08 by fmontser         ###   ########.fr       */
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


static void	_get_term_list(t_parser *context, t_prompt *prompt, t_sterm *head)
{
	int	i;

	context->_split = ft_split(prompt->_input, ' ');
	i = 0;
	head = new_sterm();
	head->text = context->_split[i];
	head->type = head->get_type(context->_split[i++]);
	while(context->_split[i])
	{
		head->next = new_sterm();
		head->next->prev = head;
		head->next->text = context->_split[i];
		head->next->type = head->get_type(context->_split[i++]);
		head = head->next;
	}
	while(i-- > 0)
	{
		//TODO NO podemos determinar si es un CMD sin compararlo con los nombres de los comandos disponibles en:
		//	- comandos residentes en ruta absoluta
		//	- comandos residentes en ruta relativa
		//	- comandos residentes en PATH
		// Existe este termino en este directorio?
		if (head->type == TEXT && (!head->prev || head->prev->type != TEXT))
			head->type = CMD;
		else if (head->type == TEXT)
			head->type = ARG;
		if (head->prev)
			head = head->prev;
	}
}

static bool	_validate_input(t_sterm *term_list)
{
	t_sterm *head;
	int	counter[TERMTYPES];
	//TODO blockeado mientras no resolvemos CMD (identificarlo)
	head = term_list;
	while (head->next)
	{
		counter[head->type]++;
		if (head->type == PIPE && (!head->next || !head->prev))
			return (false);
		head = head->next;
	}
	if (counter[CMD] == 0)
		return (false);
	return (true);
}

//Parse user input via prompt object
static void	_parse_prompt(t_parser *context, t_prompt *prompt)
{
	t_sterm	*term_list;

	term_list = NULL;
	_get_term_list(context, prompt, term_list);
	if (!_validate_input(term_list))
	{
		printf("error!");
		return ;
	}
}

//Create new process object
t_parser	new_parser(void)
{
	t_parser	new;

	new.destroy = _destructor;
	new.parse = _parse_prompt;
	return (new);
}
