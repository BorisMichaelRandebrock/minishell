/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/28 13:12:50 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"

bool	_is_op(char *str)
{
	if (*str == '<' || *str == '>' || *str == '|')
		return (1);
	return (0);
}

void	typify_token(t_list *tkn_lst)
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
		if (_prev == NULL || _prev_tkn->string[0] == '|')
			_tkn->type = CMD;
		else if (_is_op(_tkn->string))
			_tkn->type = OP;
		else
			_tkn->type = ARG;
		_tkn->optype = PIPE;		//TODO si es posible no asignar nada si no es un op
		if (_tkn->string[0] != '|')
			_tkn->optype = REDIR;
		_prev = _lst;
		_tkn = (t_token *)_lst->next;
		_lst = _lst->next;
	}
}

static void	_extract_token(char *start, char *end)
{
	t_shell	*sh;
	t_token	*tkn;
	t_list	*tmp;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = ++end - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_addfree(ft_substr(start, 0, length));
	tkn->string = sh_addfree(ft_strtrim(substr, WHSPC_CHRS));
	tmp = sh_addfree(ft_lstnew(tkn));
	if (!sh->tkn_lst)
		sh->tkn_lst = tmp;
	else
		ft_lstadd_back(&sh->tkn_lst, tmp);
}

void	_extract_op(char *raw)
{
	t_shell	*sh;
	t_token	*tkn;
	t_list	*tmp;
	char	*substr;
	int		op_sz;

	sh = get_shell();
	op_sz = 1;
	if ((*raw == '<' || *raw == '>') && *raw == *(raw + 1))
		op_sz = 2;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_addfree(ft_substr(raw, 0, op_sz));
	tkn->string = substr;
	tmp = sh_addfree(ft_lstnew(tkn));
	if (!sh->tkn_lst)
		sh->tkn_lst = tmp;
	else
		ft_lstadd_back(&sh->tkn_lst, tmp);
}

// Parse a raw prompt into token list
void	parse(char *raw)
{
	char	*start;
	char	dlmt;

	raw = sh_addfree(ft_strtrim(raw, WHSPC_CHRS));
	if (*raw == '\0')
		return ;
	dlmt = SPC_CH;
	while (ft_strchr(WHSPC_CHRS, *raw))
		raw++;
	if (*raw == DQU_CH || *raw == SQU_CH)
		dlmt = *raw;
	if (*raw == '<' || *raw == '>' || *raw == '|')
	{
		_extract_op(raw);
		return (parse(++raw));
	}
	start = raw;
	while (*(++raw) != dlmt && *raw)
		;
	_extract_token(start, raw);
	parse(++raw);
}
