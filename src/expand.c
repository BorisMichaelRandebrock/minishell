/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/28 11:20:37 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#define POS			0
#define START		1
#define VAR_OFFSET	2
/*
//TODO
$ si le sigue un whspc o nul entoncces es un caracter
$VAR encontrada se substituye por tal.
$VAR no encontrada, se elimina hasta el proximo whscp o el final.
//TODO
mas de una var... $VAR$VAR
*/

size_t	_rebuild_token(t_token *tkn, char *var_name, size_t str_sz, size_t pos[2])
{
	size_t	alloc_sz;
	size_t	exp_sz;
	char	*exp;
	char	*tail;
	char	*buff;

	exp = read_env(var_name);
	exp = ft_strchr(exp, '=') + CH_SZ;
	exp_sz = ft_strlen(exp);
	alloc_sz = (str_sz - (pos[POS] - pos[START])) + exp_sz;
	tail = sh_addfree(ft_strdup(&tkn->string[pos[START] + VAR_OFFSET]));
	buff = tkn->string;
	tkn->string = sh_calloc(1, alloc_sz);
	ft_strlcpy(tkn->string, buff, pos[START] + CH_SZ);
	ft_strlcpy(&tkn->string[pos[START]], exp, exp_sz);
	tkn->string = sh_addfree(ft_strjoin(tkn->string, tail));
	return (pos[START] + exp_sz - CH_SZ);
}

void expand_var(void *tkn)
{
	t_token	*_tkn;
	size_t	pos[2];
	size_t	str_sz;
	char	var_name[BUFF_1KB];

	_tkn = (t_token *)tkn;
	ft_memcpy(pos, (size_t[]){0, 0}, sizeof(pos));
	str_sz = ft_strlen(_tkn->string);
	if (_tkn->string[0] == SQU_CH && _tkn->string[str_sz] == SQU_CH)
		return ;
	while(_tkn->string[pos[POS]])
	{
		str_sz = ft_strlen(_tkn->string);
		if (_tkn->string[pos[POS]] == DOLL_CH)
		{
			pos[START] = pos[POS];
			while (_tkn->string[pos[POS]] != SPC_CH
				&& _tkn->string[pos[POS]] != NUL_CH
				&& _tkn->string[pos[POS]] != DQU_CH)
				pos[POS]++;
			ft_strlcpy(var_name, &_tkn->string[pos[START] + CH_SZ],
				(pos[POS] - pos[START]));
			pos[POS] = _rebuild_token(_tkn, var_name, str_sz, pos);
			continue ;
		}
		pos[POS]++;
	}
	printf("%s\n", _tkn->string); //TODO test borrar
}

/* static void	_dequote_token(t_token *tkn)
{
	t_shell	*sh;
	t_list	*tmp;

	sh = get_shell();
	tmp = sh->tkn_lst;
	if (tkn->type == ARG || tkn->type == CMD)
	{
		if (tkn->string[0] == DQU_CH || tkn->string[0] == SQU_CH)
			tkn->string++;
		if (tkn->string[ft_strlen(tkn->string) - 1] == DQU_CH
			|| tkn->string[ft_strlen(tkn->string) - 1] == SQU_CH)
			tkn->string[ft_strlen(tkn->string) - 1] = NUL_CH;
	}
	// TODO limpiar las comillas
} */
