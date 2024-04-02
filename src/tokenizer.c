/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/04/02 13:39:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"
#define NQUOTES 2
#define NON_OP_VALUES 2

static void	_dequote_token(t_token *tkn)
{
	char	*_str;

	_str = tkn->str;
	if (tkn->type == ARG || tkn->type == CMD)
	{
		if ((_str[0] == DQU_CH && _str[ft_strlen(_str) - 1] == DQU_CH)
			|| (_str[0] == SQU_CH && _str[ft_strlen(_str) - 1] == SQU_CH))
		{
			ft_memmove(_str, &_str[1], ft_strlen(_str) - NQUOTES);
			_str[ft_strlen(_str) - NQUOTES] = NUL_CH;
		}
	}
}

static void	_typify_token(void)
{
	t_tkntype	prevtype;
	t_token		*_tkn;
	t_list		*_lst;

	prevtype = NONE;
	_lst = get_shell()->tknlst;
	while (_lst)
	{
		_tkn = _lst->content;
		if (_tkn->type > NON_OP_VALUES)
		{
			prevtype = _tkn->type;
			_lst = _lst->next;
			continue ;
		}
		if (prevtype == NONE || prevtype == PIPE)
			prevtype = CMD;
		else
			prevtype = ARG;
		_tkn->type = prevtype;
		_dequote_token(_tkn);
		_lst = _lst->next;
	}
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
	token_expansion(tkn);
	ft_lstadd_back(&sh->tknlst, sh_guard(ft_lstnew(tkn), NULL));
}

char	*_extract_op_token(char *input)
{
	t_shell	*sh;
	t_token	*tkn;
	char	*substr;
	int		op_sz;

	sh = get_shell();
	tkn = sh_calloc(1, sizeof(t_token));
	op_sz = 1;
	if (*(input + 1) == *input)
	{
		op_sz = 2;
		if (*input == '<')
			tkn->type = RDHDOC;
		else if (*input == '>')
			tkn->type = RDAPP;
	}
	else
		tkn->type = *input;
	substr = sh_guard(ft_substr(input, 0, op_sz), NULL);
	tkn->str = substr;
	if (op_sz == 2)
		input++;
	ft_lstadd_back(&sh->tknlst, sh_guard(ft_lstnew(tkn), NULL));
	return (input);
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
		dlmt = SPC_CH;
		while (ft_strchr(WHSPC_CHRS, *_input))
			_input++;
		if (*_input == DQU_CH || *_input == SQU_CH)
			dlmt = *_input;
		if (*_input == '<' || *_input == '>' || *_input == '|')
			_input = _extract_op_token(_input);
		else
		{
			tkn_start = _input;
			while (*(++_input) != dlmt && *_input)
				;
			_extract_token(tkn_start, _input);
		}
		_input++;
	}
	sh_free(&input);
	_typify_token();
}
