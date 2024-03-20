/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/03/20 17:14:37 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"
#define NQUOTES 2

//TODO es posible  mejorar la integracion de este
static void	_typify(void)
{
	t_list	*_prev;
	t_list	*_lst;
	t_token	*_tkn;
	t_token	*_prev_tkn;

	_prev = NULL;
	_lst = get_shell()->tkn_lst;
	while (_lst)
	{
		_tkn = (t_token *)_lst->content;
		if (_prev)
			_prev_tkn = (t_token *)_prev->content;
		if (_prev == NULL || _prev_tkn->str[0] == '|')
			_tkn->type = CMD;
		else if (*_tkn->str == '<' || *_tkn->str == '>' || *_tkn->str == '|')
		{
			if (*(_tkn->str + 1) == *_tkn->str)
			{
				if (*_tkn->str == '<')
					_tkn->type = RDHDOC;
				else if (*_tkn->str == '>')
					_tkn->type = RDAPP;
			}
			else
				_tkn->type = *_tkn->str;
		}
		else
			_tkn->type = ARG;
		_prev = _lst;
		_lst = _lst->next;
	}
}

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

static void	_extract_token(char *start, char *end)
{
	t_shell	*sh;
	t_token	*tkn;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = (end+1) - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_guard(ft_substr(start, 0, length), NULL);
	tkn->str = sh_guard(ft_strtrim(substr, WHSPC_CHRS), substr);
	token_expansion(tkn);
	_dequote_token(tkn);
	ft_lstadd_back(&sh->tkn_lst, sh_guard(ft_lstnew(tkn), NULL));
}

char	*_extract_op_token(char *input)
{
	t_shell	*sh;
	t_token	*tkn;
	char	*substr;
	int		op_sz;

	sh = get_shell();
	op_sz = 1;
	if ((*input == '<' || *input == '>') && *input == *(input + 1))
		op_sz = 2;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_guard(ft_substr(input, 0, op_sz), NULL);
	if (op_sz == 2)
		input++;
	tkn->str = substr;
	ft_lstadd_back(&sh->tkn_lst, sh_guard(ft_lstnew(tkn), NULL));
	return(input);
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
	free(input);
	_typify();
}
