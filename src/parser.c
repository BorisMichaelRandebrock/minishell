/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/21 13:18:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v\0"

// Set token type for a list
static void	_typify_tokens(void	*tkn)
{
	static int	index = 0;
	t_token		*_tkn;

	_tkn = (t_token *)tkn;
	if (index++ == 0)
		_tkn->type = CMD;
	else
		_tkn->type = ARG;
}

// Extract a token with a range to a list
static void	_extract_token(char *raw, int start, int end)
{
	t_shell	*sh;
	t_token	*tkn;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = ++end - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_addfree(ft_substr(raw, start, length));
	tkn->string = sh_addfree(ft_strtrim(substr, WHSPC_CHRS));
	if (!sh->tkn_lst)
		sh->tkn_lst = ft_lstnew(tkn);
	else
		ft_lstadd_back(&sh->tkn_lst, ft_lstnew(tkn));
}

//Find a token and set range for extraction
static void	_find_token(char *raw, int i, bool *flag)
{
	static int	start = 0;
	static int	end = 0;
	static char	dlmt = SPC_CH;

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

//Parse a raw prompt into token list
void	parse(char *raw)
{
	t_shell	*sh;
	int		i;
	bool	flag;

	sh = get_shell();
	flag = true;
	i = 0;
	raw = sh_addfree(ft_strtrim(raw, WHSPC_CHRS));
	while (raw[i])
	{
		if (raw[i] == SPC_CH && !flag)
		{
			i++;
			continue ;
		}
		_find_token(raw, i, &flag);
		i++;
	}
	ft_lstiter(sh->tkn_lst, _typify_tokens);
}
