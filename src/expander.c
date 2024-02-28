/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/28 20:01:22 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_get_var_name(char *var_name, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != SPC_CH && str[i] != SQU_CH && str[i] != DQU_CH)
	{
		if (str[i] == DOLL_CH && i > 0)
			break ;
		i++;
	}
	ft_strlcpy(var_name, &str[1], i);
}

char	*_alloc_expansion(char *str)
{
	size_t	alloc_sz;
	size_t	i;
	char	*exp;
	char	*alloc;
	char	var_name[BUFF_1KB];

	alloc_sz = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLL_CH)
		{
			_get_var_name(var_name, &str[i]);
			alloc_sz -= ft_strlen(var_name) + CH_SZ;
			exp = read_env(var_name);
			alloc_sz += ft_strlen(exp);
		}
		i++;
	}
	alloc = sh_calloc(1, alloc_sz);
	return (alloc);
}

void	expand_var(t_token *tkn)
{
	int		i;
	int		j;
	char	*str;
	char	*exp;
	char	var_name[BUFF_1KB];

	str = tkn->str;
	tkn->str = _alloc_expansion(tkn->str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == DOLL_CH)
		{
			_get_var_name(var_name, &str[i]);
			exp = read_env(var_name);
			ft_memcpy(&tkn->str[j], exp, ft_strlen(exp));
			i += ft_strlen(var_name) + CH_SZ;
			j += ft_strlen(exp);
			continue ;
		}
		else
			tkn->str[j++] = str[i++];
	}
}
