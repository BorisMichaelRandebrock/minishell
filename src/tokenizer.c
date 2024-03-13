/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/03/13 14:29:13 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"
#define NQUOTES 2

//TODO es posible  mejorar la integracion de este
static void	_typify(t_list *tkn_lst)
{
	t_list	*_prev;
	t_list	*_lst;
	t_token	*_tkn;
	t_token	*_prev_tkn;

	_prev = NULL;
	_lst = tkn_lst;
	while (_lst)
	{
		_tkn = (t_token *)_lst->content;
		if (_prev)
			_prev_tkn = (t_token *)_prev->content;
		if (_prev == NULL || _prev_tkn->str[0] == '|')
			_tkn->type = CMD;
		else if (*_tkn->str == '<' || *_tkn->str == '>' || *_tkn->str == '|')
			_tkn->type = OP;
		else
			_tkn->type = ARG;
		_tkn->optype = PIPE;		//TODO si es posible no asignar nada si no es un op
		if (_tkn->str[0] != '|')
			_tkn->optype = REDIR;
		_prev = _lst;
		_tkn = (t_token *)_lst->next;
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
	t_list	*node;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = ++end - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_guard(ft_substr(start, 0, length), NULL);
	tkn->str = sh_guard(ft_strtrim(substr, WHSPC_CHRS), substr);
	if (tkn->str[0] != SQU_CH
		&& tkn->str[ft_strlen(tkn->str) - 1] != SQU_CH)
		expand_var(tkn);
	_dequote_token(tkn);
	node = sh_guard(ft_lstnew(tkn), NULL);
	if (!sh->tkn_lst) //TODO simpleficar gestion lista (solo addback)
		sh->tkn_lst = node;
	else
		ft_lstadd_back(&sh->tkn_lst, node);
}

void	_extract_op_token(char *input)
{
	t_shell	*sh;
	t_token	*tkn;
	t_list	*tmp;
	char	*substr;
	int		op_sz;

	sh = get_shell();
	op_sz = 1;
	if ((*input == '<' || *input == '>') && *input == *(input + 1))
		op_sz = 2;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_guard(ft_substr(input, 0, op_sz), NULL);
	tkn->str = substr;
	tmp = sh_guard(ft_lstnew(tkn), NULL);
	if (!sh->tkn_lst)	//TODO simpleficar gestion lista (solo addback)
		sh->tkn_lst = tmp;
	else
		ft_lstadd_back(&sh->tkn_lst, tmp);
}

// Parse a input prompt into token list
void	tokenizer(char *raw_input, t_list *tkn_lst)
{
	char	*input;
	char	*start;
	char	dlmt;

	input = sh_guard(ft_strtrim(raw_input, WHSPC_CHRS), raw_input);
	while (*input)
	{
		dlmt = SPC_CH;
		while (ft_strchr(WHSPC_CHRS, *input))
			input++;
		if (*input == DQU_CH || *input == SQU_CH)
			dlmt = *input;
		if (*input == '<' || *input == '>' || *input == '|')
			_extract_op_token(input);
		else
		{
			start = input;
			while (*(++input) != dlmt && *input)
				;
			_extract_token(start, input);
		}
		input++;
	}
	free(input);
	_typify(tkn_lst);
}
//TODO intentar integrar typify en el parser...cambiar a tokenizer..



/*
	t_shell *sh = get_shell();
	while(sh->tkn_lst)
	{
		printf("%s\n", ((t_token *)sh->tkn_lst->content)->str);
		sh->tkn_lst = sh->tkn_lst->next;
	}

 */

//BAK
/*
void	parse(char *input)
{
	char	*start;
	char	*buffer;
	char	dlmt;

	if (*input == '\0')
		return ;
	buffer = sh_guard(ft_strtrim(input, WHSPC_CHRS), input);
	input = buffer;
	dlmt = SPC_CH;
	while (ft_strchr(WHSPC_CHRS, *input))
		input++;
	if (*input == DQU_CH || *input == SQU_CH)
		dlmt = *input;
	if (*input == '<' || *input == '>' || *input == '|')
	{
		_extract_op(input);
		return (parse(++input));
	}
	start = input;
	while (*(++input) != dlmt && *input)
		;
	_extract_token(start, input);
	parse(++input);
	if (buffer)
		free(buffer);
}
 */
