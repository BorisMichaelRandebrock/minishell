/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/10 17:02:20 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "minishell.h"
#include "libft.h"

#define N_TOKEN_TYPES 9

//Free process object resources
static void	_destructor(t_parser *parser)
{
	int	i;

	i = 0;
	while(parser->_split[i])
	{
		free(parser->_split[i]); //TODO check leaks!
		i++;
	}
}


static void	_get_term_list(t_parser *parser, t_prompt *prompt, t_token *head_token)
{
	int	i;

	parser->_split = ft_split(prompt->_input, ' ');
	i = 0;
	head_token = new_token();
	head_token->text = parser->_split[i];
	head_token->type = head_token->get_type(parser->_split[i++]);
	while(parser->_split[i])
	{
		head_token->next = new_token();
		head_token->next->prev = head_token;
		head_token->next->text = parser->_split[i];
		head_token->next->type = head_token->get_type(parser->_split[i++]);
		head_token = head_token->next;
	}
	while(i-- > 0)
	{
		//TODO NO podemos determinar si es un CMD sin compararlo con los nombres de los comandos disponibles en:
		//	- comandos residentes en ruta absoluta
		//	- comandos residentes en ruta relativa
		//	- comandos residentes en PATH
		// Existe este termino en este directorio?
		if (head_token->type == TEXT && (!head_token->prev || head_token->prev->type != TEXT))
			head_token->type = CMD;
		else if (head_token->type == TEXT)
			head_token->type = ARG;
		if (head_token->prev)
			head_token = head_token->prev;
	}
}

static bool	_validate_input(t_token *token_lst)
{
	t_token *head;
	int	counter[N_TOKEN_TYPES];
	//TODO blockeado mientras no resolvemos CMD (identificarlo)
	head = token_lst;
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
static void	_parse_prompt(t_prompt *prompt)
{
	t_token	*token_lst;

	token_lst = NULL;
	_get_term_list(&prompt->_shell->_parser, prompt, token_lst);
	if (!_validate_input(token_lst))
	{
		printf("error!");
		return ;
	}
}

//Create new process object
t_parser	new_parser(t_shell *shell)
{
	t_parser	new;

	new._shell = shell;
	new.destroy = _destructor;
	new.parse = _parse_prompt;
	return (new);
}
