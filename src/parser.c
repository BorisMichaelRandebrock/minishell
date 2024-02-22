/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/22 19:39:01 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"


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
	t_token *tkn;
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
	tkn->type = OP;	//TODO unificar?
	tmp = sh_addfree(ft_lstnew(tkn));
	if (!sh->tkn_lst)
		sh->tkn_lst = tmp;
	else
		ft_lstadd_back(&sh->tkn_lst, tmp);
}

//Parse a raw prompt into token list
void	parse(char *raw)
{
	char	*start;
	char	dlmt;

	if(*raw == '\0')
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
