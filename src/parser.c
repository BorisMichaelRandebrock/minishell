/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/23 20:02:37 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#define WHSPC_CHRS " \t\n\r\f\v"

/*
//TODO
$ si le sigue un whspc o nul entoncces es un caracter
$VAR encontrada se substituye por tal.
$VAR no encontrada, se elimina hasta el proximo whscp o el final.
//TODO
mas de una var... $VAR$VAR
*/
static void _expand_vars(char *tkn_str)
{
	t_shell	*sh;
	size_t	str_sz;
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	alloc_sz;
	char	def[BUFF_1KB];
	char	*var;

	char	**_env = get_shell()->env->sys_env;

	start = 0;
	end = 0;
	str_sz = ft_strlen(tkn_str);
	sh = get_shell();
	i = 0;
	if (tkn_str[0] == SQU_CH && tkn_str[str_sz] == SQU_CH)
		return ;
	while(tkn_str[i])
	{
		if (tkn_str[i] == DOL_CH)
		{
			start = i;
			while (tkn_str[++i] != SPC_CH)
				;
			end = i;
			ft_strlcpy(def, &tkn_str[start + CH_SZ], (end - start));
			//TODO es necesario hacer un refactor del ENV, pasarlo a un archivo tempporal.
			var = get_env_var(_env, def);
			var = ft_strchr(var, '=');
			var++;
			alloc_sz = (str_sz - (end - start)) + ft_strlen(var);
			tkn_str = sh_addfree(ft_realloc(tkn_str, alloc_sz)); //TODO leak, realloc libera por su cuenta! y luego queda vacio! ajustar free function
			ft_memmove(&tkn_str[start + ft_strlen(var)],&tkn_str[end],ft_strlen(&tkn_str[end])); //TODO no hace bien si el $NAME es mas pequeño que su valor, por jeemplo $PWD PWD=/ (3 vs 1).
			ft_memcpy(&tkn_str[start], var, ft_strlen(var));
			//i += //TODO ponerlo al final del memcpy   o   añadir la diferencia entre el recambio (necesitas numeros absolutos...)
			continue ;
		}
		i++;
	}
}

bool	_is_op(char *str)
{
	if ((*str == '<' || *str == '>') && *str == *(str + 1))
		return (1);
	if (*str == '<' || *str == '>' || *str == '|')
		return (1);
	return (0);
}

static void	_clean_token(t_token *tkn)
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
}
static void	_typify_token(t_token *tkn)
{
	t_shell	*sh;
	t_list	*prev_tkn;
	t_list	*_tkn_lst;

	prev_tkn = NULL;
	sh = get_shell();
	_tkn_lst = sh->tkn_lst;
	// while (!_tkn_lst->next->content == tkn)
	// 	_tkn_lst = _tkn_lst->next;
	// prev_tkn = sh->tkn_lst;
	while (_tkn_lst)
	{
		if (prev_tkn == NULL || (*(t_token *)prev_tkn->content).type == '|')
			tkn->type = CMD;
		else if (_is_op(tkn->string))
			tkn->type = OP;
		else
			tkn->type = ARG;
		prev_tkn = _tkn_lst;
		_tkn_lst = _tkn_lst->next;
		// TODO tipificar los token, y limpiar las comillas
		// cmd: primero o    primero despues de |.
		// args: empeiza y acaban en quotes, no son primeros,
		// pero si cuando le precede un redireccionador.
	}
}

static void	_extract_token(char *start, char *end)
{
	t_shell	*sh;
	t_token	*tkn;
	t_list	*tmp;
	size_t	length;
	char	*substr;

	sh = get_shell();
	length = ++end - start;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_addfree(ft_substr(start, 0, length));
	tkn->string = sh_addfree(ft_strtrim(substr, WHSPC_CHRS));
	_typify_token(tkn);
	tmp = sh_addfree(ft_lstnew(tkn));
	if (!sh->tkn_lst)
		sh->tkn_lst = tmp;
	else
		ft_lstadd_back(&sh->tkn_lst, tmp);
}

void	_extract_op(char *raw)
{
	t_shell	*sh;
	t_token	*tkn;
	t_list	*tmp;
	char	*substr;
	int		op_sz;

	sh = get_shell();
	op_sz = 1;
	if ((*raw == '<' || *raw == '>') && *raw == *(raw + 1))
		op_sz = 2;
	tkn = sh_calloc(1, sizeof(t_token));
	substr = sh_addfree(ft_substr(raw, 0, op_sz));
	tkn->string = substr;
	_typify_token(tkn);
	_clean_token(tkn);
	tmp = sh_addfree(ft_lstnew(tkn));
	if (!sh->tkn_lst)
		sh->tkn_lst = tmp;
	else
		ft_lstadd_back(&sh->tkn_lst, tmp);
}

// Parse a raw prompt into token list
void	parse(char *raw)
{
	char	*start;
	char	dlmt;

	if (*raw == '\0')
		return ;
	dlmt = SPC_CH;
	while (ft_strchr(WHSPC_CHRS, *raw))
		raw++;
	if (*raw == DQU_CH || *raw == SQU_CH)
		dlmt = *raw;
	if (*raw == '<' || *raw == '>' || *raw == '|')
	{
		_extract_op(raw);
		return (parse(++raw));
	}
	start = raw;
	while (*(++raw) != dlmt && *raw)
		;
	_extract_token(start, raw);
	parse(++raw);
}
