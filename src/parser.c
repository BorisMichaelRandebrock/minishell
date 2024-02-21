/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/21 14:54:51 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS "	\t\n\r\f\v\0"
#define POS				0
#define START			1
#define END				2
#define TCOUNT			3


//TODO manage operator
static bool	_is_op(char *raw)
{
	(void)raw; //TODO borrar esto...
	t_shell	*sh;

	sh = get_shell();

	// 1. identificar operador
	// 2. no lo es return FALSE y parse continua
	// 3. si lo es crear un nuevo token y agregarlo a la lista (sh->token_lst)
	// 4. lanzar parse (cursi!) desde raw + 1!
	return (false);
}

// Extract a token with a range to a list
static void	_extract_token(char *raw, int idx[4])
{
	t_shell	*sh;
	t_token	*tkn;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = ++(idx[END]) - (idx[START]);
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_addfree(ft_substr(raw, idx[START], length));
	tkn->string = sh_addfree(ft_strtrim(substr, WHSPC_CHRS));
	tkn->type = ARG;
	if (idx[TCOUNT] == 0)
		tkn->type = CMD;
	idx[TCOUNT]++;
	if (!sh->tkn_lst)
		sh->tkn_lst = ft_lstnew(tkn);
	else
		ft_lstadd_back(&sh->tkn_lst, ft_lstnew(tkn));
}

//Find a token and set range for extraction
static void	_find_token(char *raw, int idx[4], bool *flag, char *dlmt)
{
	if (!*flag)
	{
		if (raw[idx[POS]] == SQU_CH || raw[idx[POS]] == DQU_CH)
			*dlmt = raw[idx[POS]];
		else
			*dlmt = SPC_CH;
		*flag = true;
		idx[START] = idx[POS];
	}
	else if ((raw[idx[POS]] == *dlmt || raw[idx[POS] + 1] == NUL_CH) && *flag)
	{
		*flag = false;
		idx[END] = idx[POS];
		_extract_token(raw, idx);
	}
}

//Parse a raw prompt into token list
void	parse(char *raw)
{
	int		idx[4];
	char	dlmt;
	bool	flag;

	ft_memcpy(idx, (int []){0, 0, 0, 0}, sizeof(idx));
	dlmt = SPC_CH;
	flag = true;
	raw = sh_addfree(ft_strtrim(raw, WHSPC_CHRS));
	while (raw[idx[POS]])
	{
		if(_is_op(raw))
			break ;
		if (raw[idx[POS]] == SPC_CH && !flag)
		{
			idx[POS]++;
			continue ;
		}
		_find_token(raw, idx, &flag, &dlmt);
		idx[POS]++;
	}
}
