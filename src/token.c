/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/06 21:56:07 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"

static void	_pre_typify(t_token *tkn)
{
	if (*tkn->str == '<')
	{
		tkn->type = RDIN;
		if (*(tkn->str + 1) == '<')
			tkn->type = RDHDOC;
	}
	else if (*tkn->str == '>')
	{
		tkn->type = RDOUT;
		if (*(tkn->str + 1) == '>')
			tkn->type = RDAPP;
	}
	else if (*tkn->str == '|')
		tkn->type = PIPE;
	else
		tkn->type = ARG;
}

static void	_extract_token(char *start, char *end)
{
	t_shell	*sh;
	t_token	*tkn;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = (end + 1) - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_guard(ft_substr(start, 0, length), NULL);
	tkn->str = sh_guard(ft_strtrim(substr, WHSPC_CHRS), substr);
	_pre_typify(tkn);
	token_expansion(tkn);
	ft_lstadd_back(&sh->tknlst, sh_guard(ft_lstnew(tkn), NULL));
}
// Parse a input prompt into a token list
void	tokenizer(char *input)
{
	char	*_input;
	char	*tkn_start;
	char	dlmt;

	_input = input;
	while (*_input)
	{
		dlmt = ' ';
		while (ft_strchr(WHSPC_CHRS, *_input))
			_input++;
		if (*_input == '"' || *_input == '\'')
			dlmt = *_input;
		tkn_start = _input;
		while (*(++_input) != dlmt && *_input)
			;
		_extract_token(tkn_start, _input);
		_input++;
	}
	sh_free(&input);
}
