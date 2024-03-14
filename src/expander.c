/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/14 12:24:15 by fmontser         ###   ########.fr       */
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
	var_name[i++] = EQ_CH;
	var_name[i] = NUL_CH;
}
//TODO  BUG!! los varnames necesitan el '=' al final!
char	*_alloc_expansion(char *str)
{
	size_t	alloc_sz;
	size_t	i;
	char	*exp;
	char	*alloc;
	char	var_name[BUFSIZ];

	alloc_sz = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLL_CH)
		{
			_get_var_name(var_name, &str[i]);
			alloc_sz -= ft_strlen(var_name - EQ_CH) + CH_SZ;
			exp = get_evar(var_name);
			alloc_sz += ft_strlen(exp);
		}
		i++;
	}
	alloc = sh_calloc(1, alloc_sz + NUL_SZ);
	return (alloc);
}
//TODO @@@@ BUG!! los varnames necesitan el '=' al final!
void	expand_var(t_token *tkn)
{
	int		i;
	int		j;
	char	*str;
	char	*exp;
	char	var_name[BUFSIZ];

	str = tkn->str;
	tkn->str = _alloc_expansion(tkn->str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != DOLL_CH)
			tkn->str[j++] = str[i++];
		else
		{
			_get_var_name(var_name, &str[i]);
			exp = get_evar(var_name);
			ft_memcpy(&tkn->str[j], exp, ft_strlen(exp));
			i += ft_strlen(var_name - EQ_CH) + CH_SZ;
			j += ft_strlen(exp);
		}
	}
	free(str);
}
