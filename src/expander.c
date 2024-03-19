/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/19 16:29:51 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define START	0
#define END		1

char	*_get_var_name(char *str)
{
	char	*var_name;
	size_t	i;

	var_name = sh_guard(ft_strdup(++str), NULL); //TODO si aparece el dollar...
	i = 0;
	while (var_name[i] && var_name[i] != SPC_CH && var_name[i] != DQU_CH
		&& var_name[i] != '$')
		i++;
	var_name[i++] = '=';
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

void	_expand_var(t_token *tkn)
{
	char	_str[BUF_1KB + NUL_SZ];
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_memset(_str, '\0', BUF_1KB);
	while(tkn->str[i])
	{
		if (tkn->str[i] == '$')
		{
			name = _get_var_name(&tkn->str[i]);
			value = get_evar(name);
			while(value && *value)
				_str[j++] = *(value++);
			i += ft_strlen(name);
			free(name);
		}
		if (tkn->str[i] != '$')
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
	if (tkn->str[i] == SQU_CH && tkn->str[size - IDX_OFFST] == SQU_CH)
		return ;
	_expand_var(tkn);
}
