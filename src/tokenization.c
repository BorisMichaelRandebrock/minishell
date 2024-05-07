/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/05/07 12:11:10 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define WHSPC_CHRS	" \t\n\r\f\v"

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

static void	_save_token(char *buffer)
{
	t_shell	*sh;
	t_token	*tkn;

	sh = get_shell();
	tkn = sh_calloc(1, sizeof(t_token));
	tkn->str = sh_guard(ft_strdup(buffer), NULL);
	_pre_typify(tkn);
	if (tkn->type == ARG)
		token_expansion(tkn);
	ft_lstadd_back(&sh->tknlst, sh_guard(ft_lstnew(tkn), NULL));
}

static int	_extract_op_token(char *start)
{
	char	buffer[BUF_1KB];

	ft_memset(buffer, '\0', BUF_1KB);
	buffer[0] = *start;
	if (*start == *(start + 1) && *start != '|')
		buffer[1] = *(start + 1);
	_save_token(buffer);
	return (ft_strlen(buffer));
}

static int	_extract_token(char *start, char dlmt)
{
	char	buffer[BUF_1KB];
	int		i;

	ft_memset(buffer, '\0', BUF_1KB);
	i = 0;
	if (dlmt != ' ')
	{
		buffer[i] = start[i];
		i++;
	}
	while ((start[i] != dlmt && start[i] != '\0'))
	{
		if ((start[i] == '>' || start[i] == '<' || start[i] == '|')
			&& (dlmt != '\'' && dlmt != '\"'))
			break ;
		buffer[i] = start[i];
		i++;
	}
	if (dlmt != ' ')
	{
		buffer[i] = start[i];
		i++;
	}
	_save_token(buffer);
	return (i);
}

void	tokenizer(char *input)
{
	char	*_input;
	char	*tkn_start;
	char	dlmt;

	_input = input;
	if (!input)
		sh_ctrld_handler();
	while (*_input)
	{
		dlmt = ' ';
		while (ft_strchr(WHSPC_CHRS, *_input) && !ft_strchr("\0", *_input))
			_input++;
		if (*_input == '>' || *_input == '<' || *_input == '|')
		{
			_input += _extract_op_token(_input);
			continue ;
		}
		if (*_input == '"' || *_input == '\'')
			dlmt = *_input;
		tkn_start = _input;
		if (*_input)
			_input += _extract_token(tkn_start, dlmt);
	}
	ft_memset(input, '\0', ft_strlen(input));
	sh_free(&input);
}
