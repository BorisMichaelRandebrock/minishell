/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/14 13:46:23 by brandebr         ###   ########.fr       */
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
	while (parser->_split[i])
	{
		free(parser->_split[i]); // TODO check leaks!
		i++;
	}
	parser->_tokens->destroy(parser->_tokens);
	free(parser);
}

// TODO NO podemos determinar si es un CMD sin compararlo con los nombres de los comandos disponibles en:
//	- comandos residentes en ruta absoluta
//	- comandos residentes en ruta relativa
//	- comandos residentes en PATH
// Existe este termino en este directorio? echo "hola""adios"

// echo    "hola   ' " que '   tal"' | cat -e
char	**masked_split(t_prompt *prompt)
{
	int	i;
	int	prevmask;
	int	currmask;
	int	count;

	i = 0;
	count = 0;
	while (prompt->_input[i])
	{
		currmask = ft_atoi(&prompt->_mask[i]);
		if ((prompt->_input[i] == SPC_CH && prompt->_mask[i] == '0')
			|| (prompt->_input[i] != SPC_CH && (currmask > prevmask
					&& currmask > 0)))
			count++;
		prevmask = currmask;
		i++;
	}
	return (NULL);
}


static void	_get_tokens(t_parser *parser, t_prompt *prompt)
{
	int	i;

	parser->_split = masked_split(prompt);
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
}

// Parse user input via prompt object
static void	_parse_prompt(t_prompt *prompt)
{
	// TODO separar qtokens
	_get_tokens(prompt->_shell->_parser, prompt);
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
	new->_tokens = new_token(shell);
	new->destroy = _destructor;
	new->parse = _parse_prompt;
	return (new);
}
