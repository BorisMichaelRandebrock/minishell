/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/28 14:23:30 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#define I			0
#define SP			1
#define VAR_OFFSET	2
#define NQUOTES		2
/*
//TODO
$ si le sigue un whspc o nul entoncces es un caracter
$VAR encontrada se substituye por tal.
$VAR no encontrada, se elimina hasta el proximo whscp o el final.
//TODO
mas de una var... $VAR$VAR
*/

void	dequote_token(void *tkn)
{
	t_token	*_tkn;
	char	*_str;

	_tkn = (t_token *)tkn;
	_str = _tkn->string;
	if (_tkn->type == ARG || _tkn->type == CMD)
	{
		if ((_str[0] == DQU_CH && _str[ft_strlen(_str) - 1] == DQU_CH)
			||(_str[0] == SQU_CH && _str[ft_strlen(_str) - 1] == SQU_CH))
		{
			ft_memmove(_str, &_str[1], ft_strlen(_str) - NQUOTES);
			_str[ft_strlen(_str) - NQUOTES] = NUL_CH;
		}
	}
}

//TODO $X'asd'
size_t	_rebuild_token(t_token *tkn, char *var_name, size_t str_sz, size_t i[2])
{
	size_t	alloc_sz;
	size_t	exp_sz;
	char	*exp;
	char	*tail;
	char	*buff;

	exp = read_env(var_name);
	if (!exp)
	{
		exp_sz =  ft_strlen(var_name) + CH_SZ;
		ft_memmove(&tkn->string[i[SP]], &tkn->string[i[SP] + exp_sz],
			ft_strlen(&tkn->string[exp_sz]) + NUL_SZ);
		return (0);
	}
	exp = ft_strchr(exp, '=') + CH_SZ;
	exp_sz = ft_strlen(exp);
	alloc_sz = (str_sz - (i[I] - i[SP])) + exp_sz;
	tail = sh_addfree(ft_strdup(&tkn->string[i[SP] + VAR_OFFSET]));
	buff = tkn->string;
	tkn->string = sh_calloc(1, alloc_sz);
	ft_strlcpy(tkn->string, buff, i[SP] + CH_SZ);
	ft_strlcpy(&tkn->string[i[SP]], exp, exp_sz);
	tkn->string = sh_addfree(ft_strjoin(tkn->string, tail));
	return (i[SP] + exp_sz - CH_SZ);
}

//TODO $_'asd'
static void	_get_var_name(char *var_name, char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != SPC_CH && str[i] != SQU_CH && str[i] != DQU_CH)
		i++;
	ft_strlcpy(var_name, &str[1], i);
}


//TODO @@@@@@ mala gestion leaks
void expand_var(void *tkn)
{
	t_token	*_tkn;
	size_t	i[2];
	size_t	str_sz;
	char	var_name[BUFF_1KB];

	_tkn = (t_token *)tkn;
	ft_memcpy(i, (size_t[]){0, 0}, sizeof(i));
	str_sz = ft_strlen(_tkn->string);
	if (_tkn->string[0] == SQU_CH && _tkn->string[str_sz - 1] == SQU_CH)
		return ;
	while(_tkn->string[i[I]])
	{
		str_sz = ft_strlen(_tkn->string);
		if (_tkn->string[i[I]] == DOLL_CH)
		{
			i[SP] = i[I];
			while (_tkn->string[i[I]] != SPC_CH && _tkn->string[i[I]] != NUL_CH
				&& _tkn->string[i[I]] != DQU_CH)
				i[I]++;
			_get_var_name(var_name, &_tkn->string[i[SP]]);
			i[I] = _rebuild_token(_tkn, var_name, str_sz, i);
			continue ;
		}
		i[I]++;
	}
}
