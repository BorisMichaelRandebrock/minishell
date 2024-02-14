/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:28:13 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/14 13:46:23 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ok(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (0);
	return (1);
}

int	token_count(char *str)
{
	int	count;
	int	i;
	int	qflag;

	count = 0;
	i = 0;
	qflag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			qflag = !qflag;
		if (((i = 0 && ok(str[i])) && !qflag) || ((!ok(str[i]) && ok(str[i + 1])
					&& !qflag)))
			count++;
		i++;
	}
}

char	**masked_split(t_prompt *prompt)
{
	char	**res;
	int		i;
	int		j;
	int		prevmask;
	int		currmask;
	int		count;

	i = 0;
	while (prompt->_input[i])
	{
		currmask = ft_atoi(&prompt->_mask[i]);
		if (prompt->_input[i] == SPC_CH && prompt->_mask[i] == '0'
			|| prompt->_input[i] != SPC_CH && currmask > prevmask)
			count++;
		prevmask = currmask;
		i++;
	}
	return (NULL);
}
