/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/19 19:07:29 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdbool.h>



// Free process object resources
static void	_destructor(t_parser *parser)
{
	//TODO free all
	free(parser);
}

//test echo "hola ' " que 'ase| ' | cat -e | echo >> txt
static void	*_tokenize(void *raw)
{
	t_token	*new;
	size_t	end;

	new = new_token();
	new->_text = (char *)raw;
	end = ft_strlen(new->_text);
	*new->_op = new->get_op_type(new->_text);
	if (*new->_op != NONE)
		*new->_type = OP;
	else if ((new->_text[START] == DQU_CH && new->_text[end] == DQU_CH)
		|| (new->_text[START] == SQU_CH && new->_text[end] == SQU_CH))
		*new->_type = ARG;
	else
		*new->_type = TEXT;
	return (new);
}

//TODO revisar ft_lstmap con paco...leaks...
// Parse user input via prompt object
static void	_parse_prompt(t_shell *sh)
{
	sh->_parser->_tokens = ft_lstmap(sh->_prompt->_raw_list,_tokenize , free);

	//TODO tests!

	while(sh->_parser->_tokens)
	{
		t_token *_token = (t_token *)sh->_parser->_tokens->content;

		printf("%s\n", _token->_text);
		//printf("%s \t\t\t\t\t\t %i \t\t\t\t\t\t %i\n", _token->_text, (int)*_token->_type, (int)*_token->_op);
		sh->_parser->_tokens = sh->_parser->_tokens->next;
	}
	exit(0);
}

// Create new process object
t_parser	*new_parser(t_shell *shell)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		sh_exit(shell, MEM_ERROR);
	new->_shell = shell;
	new->_tokens = NULL;
	new->destroy = _destructor;
	new->parse = _parse_prompt;
	return (new);
}
