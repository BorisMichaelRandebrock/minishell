/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:40:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/18 11:37:21 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define START 0
#define END 1

static int	_extract_token(t_prompt *prompt, int start, int end)
{
	char	*raw_token;
	char	*trim_token;

	raw_token = ft_substr(prompt->_input, start, ++end - start);
	ft_memmove(&prompt->_input[start], &prompt->_input[end],
		ft_strlen(prompt->_input) + NUL_CH);
	trim_token = ft_strtrim(raw_token, " ");
	free(raw_token);
	if (*trim_token)
	{
		if (!prompt->_raw_list)
			prompt->_raw_list = ft_lstnew(trim_token);
		else
			ft_lstadd_back(&prompt->_raw_list, ft_lstnew(trim_token));
	}
	else
		free(trim_token);
	return (start);
}

static char	_get_dlmt(char c)
{
	if (c == '"' || c == '\'' || c == ' ')
		return (c);
	return ('\0');
}

static void	_set_range(bool *flag, int *rng, int i)
{
	*flag = !*flag;
	if (*flag)
		rng[START] = i;
	else
		rng[END] = i;
}

void	toklst(t_prompt *prompt)
{
	int		i;
	int		rng[2];
	bool	flag;
	char	dlmt;

	i = 0;
	ft_memcpy(rng, (int []){10, 20}, sizeof(rng));
	flag = false;
	while (prompt->_input[i])
	{
		if (!flag)
			dlmt = _get_dlmt(prompt->_input[i]);
		if (prompt->_input[i] == dlmt || dlmt == NUL_CH)
		{
			if (dlmt == NUL_CH)
				dlmt = SPC_CH;
			_set_range(&flag, rng, i);
			if (rng[START] < rng[END] && !flag)
				i = _extract_token(prompt, rng[START], rng[END]);
		}
		if (rng[START] < rng[END] && !flag)
			continue ;
		i++;
	}
	_extract_token(prompt, rng[START], rng[END]);
}
