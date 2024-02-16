/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:40:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/16 10:08:43 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SPC_CH ' '
#define NUL_CH '\0'


static int _extract_token(t_prompt *prompt, int start, int end)
{
	char *raw_token;
	char *trim_token;

	raw_token = ft_substr(prompt->_input, start, ++end - start);
	ft_memmove(&prompt->_input[start], &prompt->_input[end], ft_strlen(prompt->_input) + NUL_CH);
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
// TODO adaptar a norminette (quizas recursiva?)
void toklst(t_prompt *prompt, char *dlmt)
{
	int		i;
	int		j;
	int		start;
	int		end;
	bool	flag;
	char	_dlmt;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	flag = false;
	while (prompt->_input[i])
	{
		while (dlmt[j] && !flag)
		{
			if (prompt->_input[i] == dlmt[j])
			{
				_dlmt = dlmt[j];
				break ;
			}
			_dlmt = NUL_CH;
			j++;
		}
		if (prompt->_input[i] == _dlmt || _dlmt == NUL_CH)
		{
			if (_dlmt == NUL_CH)
				_dlmt = SPC_CH;
			flag = !flag;
			if (flag)
				start = i;
			else
				end = i;
			if (start < end && !flag)
			{
				i = _extract_token(prompt, start, end);
				continue ;
			}
		}
		j = 0;
		i++;
	}
	_extract_token(prompt, start, end);
}
