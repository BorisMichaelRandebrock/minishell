/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/10 13:17:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IDX_OFFST	1
#define QUOTES_SZ	2
#define START		0
#define END			1

//TODO //BUG token compuesto por un solo quote segfault!!
static void	_dequote_token(t_token *tkn)
{
	char	*_str;

	_str = tkn->str;
	if (tkn->type == ARG)
	{
		if ((_str[0] == '"' && _str[ft_strlen(_str) - IDX_OFFST] == '"')
			|| (_str[0] == '\'' && _str[ft_strlen(_str) - IDX_OFFST] == '\''))
		{
			ft_memmove(_str, &_str[1], ft_strlen(_str) - QUOTES_SZ);
			_str[ft_strlen(_str) - QUOTES_SZ] = '\0';
		}
	}
}

static char	*_get_var_name(char *str)
{
	char	*var_name;
	size_t	i;

	var_name = sh_guard(ft_strdup(++str), NULL);
	i = 0;
	while (var_name[i] && var_name[i] != ' ' && var_name[i] != '"'
		&& var_name[i] != '$')
		i++;
	var_name[i++] = '=';
	var_name[i] = '\0';
	return (var_name);
}

static void	_expand_var(t_token *tkn)
{
	char	_str[BUF_1KB + NUL_SZ];
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_memset(_str, '\0', BUF_1KB);
	while (tkn->str[i])
	{
		if (tkn->str[i] == '$' && tkn->str[i + 1] != '\0')
		{
			name = _get_var_name(&tkn->str[i]);
			value = get_evar(name);
			while (value && *value)
				_str[j++] = *(value++);
			i += ft_strlen(name);
			sh_free(&name);
		}
		else if (tkn->str[i] != '$' || tkn->str[i + 1] == '\0')
			_str[j++] = tkn->str[i++];
	}
	tkn->str = sh_guard(ft_strdup(_str), tkn->str);
}

void	token_expansion(t_token *tkn)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(tkn->str);
	if (tkn->str[i] != '\'' || tkn->str[size - IDX_OFFST] != '\'')
		_expand_var(tkn);
	_dequote_token(tkn);
}
