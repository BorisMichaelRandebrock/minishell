/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/18 18:03:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1

char	*_get_var_name(char *str)
{
	char	*var_name;
	size_t	i;

	i = 0;
	while (str[i++] != '$')
		;
	var_name = sh_guard(ft_strdup(&str[i]), NULL);
	i = 0;
	while (var_name[i] && var_name[i] != SPC_CH && var_name[i] != DQU_CH)
		i++;
	var_name[i] = '\0';
	return (var_name);
}
int	_get_var_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != SPC_CH && str[i] != DQU_CH)
		i++;
	return (i);
}

void	_expand_var(t_token *tkn, char *start)
{
	char	*_str;
	char	*name;
	char	*value;
	int		var_start;
	int		var_end;
	size_t	value_sz;

	name = _get_var_name(start);
	value = get_evar(name);
	value_sz = ft_strlen(value);
	var_start = (start - tkn->str);
	var_end = _get_var_end(start);
	_str = sh_guard(ft_strdup(tkn->str), NULL);
	tkn->str = ft_realloc(tkn->str, (ft_strlen(_str) + value_sz + NUL_SZ));
	ft_memcpy(tkn->str, _str, var_start);
	ft_memcpy(&tkn->str[var_start],value, value_sz);
	ft_memcpy(&tkn->str[var_start + value_sz], &_str[var_start + var_end],
		ft_strlen(&_str[var_end]) + NUL_SZ);
	free(name);
	free(_str);
}
void	token_expansion(t_token *tkn)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(tkn->str);
	if (tkn->str[i] == SQU_CH && tkn->str[size - IDX_OFFST] == SQU_CH)
		return ;
	while (tkn->str[i])
	{
		if (tkn->str[i] == '$')
			_expand_var(tkn, &tkn->str[i]);
		i++;
	}
}
