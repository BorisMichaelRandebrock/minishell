/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/13 20:28:09 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "minishell.h"
#include "libft.h"


#define N_TOKEN_TYPES 9 //TODO es necesario?

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
	free(parser);
}

//Parse user input via prompt object
static void	_parse_prompt(t_prompt *prompt)
{
	(void)prompt;
	//TODO @@@@@@@@@@ parsear el prompt usando la mascara
	// split condicionado por la mascara
	// expansion de VAR
	// construccion de tokenlist
}

//Create new process object
t_parser	*new_parser(t_shell *shell)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	new->_shell = shell;
	new->destroy = _destructor;
	new->parse = _parse_prompt;
	return (new);
}
