/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/21 00:08:13 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define	WHITE_SPCS " \t\n\r\f\v\0"

// Parse a raw prompt into tokens
static void	_extract_token(char *raw, int start, int end)
{
	t_shell	*sh;
	t_token	*tkn;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = ++end - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = ft_substr(raw, start, length);
	tkn->string = sh_addfree(ft_strtrim(substr, WHITE_SPCS));
	free(substr);
	if (!sh->tkn_lst)
		sh->tkn_lst = ft_lstnew(tkn);
	else
		ft_lstadd_back(&sh->tkn_lst, ft_lstnew(tkn));
}

static bool	_skip_whspc(char c, int *i, bool flag)
{
	if (ft_is_whspc(c) && !flag)
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static void _find_token(char *raw, int i, bool *flag)
{
	int		start;
	int		end;
	char	dlmt;

	start = 0;
	dlmt = SPC_CH;
	if (!*flag)
	{
		if (raw[i] == SQU_CH || raw[i] == DQU_CH)
			dlmt = raw[i];
		else
			dlmt = SPC_CH;
		*flag = true;
		start = i;
	}
	else if ((raw[i] == dlmt || raw[i + 1] == NUL_CH) && *flag)
	{
		*flag = false;
		end = i;
		_extract_token(raw, start, end);
	}
}

void	parse(char *raw)
{
	int		i;
	bool	flag;

	flag = true;
	i = 0;
	while (raw[i])
	{
		if (_skip_whspc(raw[i], &i, flag))
			continue ;
		_find_token(raw, i, &flag);
		i++;
	}
}
