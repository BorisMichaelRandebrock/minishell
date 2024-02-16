/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/15 20:59:58 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdbool.h>

#define N_TOKEN_TYPES 9 // TODO es necesario?

// Free process object resources
static void	_destructor(t_parser *parser)
{
	int	i;

	i = 0;
	if (parser->_split)
	{
		while (parser->_split[i])
		{
			free(parser->_split[i]); // TODO check leaks!
			i++;
		}
	}
	parser->_tokens->destroy(parser->_tokens);
	free(parser);
}

// TODO NO podemos determinar si es un CMD sin compararlo con los nombres de los comandos disponibles en:
//	- comandos residentes en ruta absoluta
//	- comandos residentes en ruta relativa
//	- comandos residentes en PATH
// Existe este termino en este directorio? echo "hola""adios"

/*
static void	_get_tokens(t_parser *parser, t_prompt *prompt)
{
	int	i;

	//parser->_split =
	i = 0;
	parser->_tokens = new_token(prompt->_shell);
	parser->_tokens->_text = parser->_split[i];
	parser->_tokens->_type = parser->_tokens->get_type(parser->_split[i++]);
	while (parser->_split[i])
	{
		parser->_tokens->_next = new_token(prompt->_shell);
		parser->_tokens->_next->_prev = parser->_tokens;
		parser->_tokens->_next->_text = parser->_split[i];
		parser->_tokens->_next->_type = parser->_tokens->get_type(parser->_split[i++]);
		parser->_tokens = parser->_tokens->_next;
	}
} */

// Parse user input via prompt object
static void	_parse_prompt(t_prompt *prompt)
{
	(void)prompt;
	// TODO separar qtokens
	//_get_tokens(prompt->_shell->_parser, prompt);
	// TODO @@@@@@@@@@ parsear el prompt usando la mascara
	// split condicionado por la mascara
	// expansion de VAR
	// construccion de tokenlist
}

// Create new process object
t_parser	*new_parser(t_shell *shell)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	new->_shell = shell;
	new->_split = NULL;
	new->_tokens = new_token(shell);
	new->destroy = _destructor;
	new->parse = _parse_prompt;
	return (new);
}
