/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:29:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 20:31:03 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
//TODO
$ si le sigue un whspc o nul entoncces es un caracter
$VAR encontrada se substituye por tal.
$VAR no encontrada, se elimina hasta el proximo whscp o el final.
//TODO
mas de una var... $VAR$VAR
*/

static void expand_vars(char *tkn_str)
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
