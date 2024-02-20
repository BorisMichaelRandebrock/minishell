/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/20 21:07:00 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// Parse a raw prompt into tokens
static t_token	*_extract_token(char *raw, int start, int end)
{
	t_token	*tkn;
	size_t	length;
	char	*substr;

	length = ++end - start;
	tkn = sh_calloc(NULL, sizeof(t_token), STRCT);
	substr = ft_substr(raw, start, length);
	tkn->string = ft_strtrim(substr, " ");
	free(substr);
	//TODO guardar el puntero en lista CNT
	return (tkn);
}

void	parse(t_shell *sh, char *raw)
{
	int		i;
	int		start;
	int		end;
	bool	flag;
	char	dlmt;

	char *debug = raw;

	flag = true;
	i = 0;
	start = 0;
	dlmt = SPC_CH;
	while (raw[i])
	{
		if (raw[i] == SPC_CH && !flag)
		{
			i++;
			debug++;
			continue ;
		}
		if (!flag)
		{
			if (raw[i] == SQU_CH || raw[i] == DQU_CH)
				dlmt = raw[i];
			else
				dlmt = SPC_CH;
			flag = true;
			start = i;
		}
		else if ((raw[i] == dlmt || raw[i + 1] == NUL_CH) && flag)
		{
			flag = false;
			end = i;
			if (!sh->tkn_lst)
				sh->tkn_lst = ft_lstnew(_extract_token(raw, start, end));
			else
				ft_lstadd_back(&sh->tkn_lst, ft_lstnew(_extract_token(raw, start, end)));
		}
		i++;
		debug++;
	}
}
