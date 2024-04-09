/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/09 13:48:26 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <string.h>

#define NEW_VAR_SZ	1
#define CH_SZ		1

//var_name format must be 'VAR='
char	*get_evar(char *var_name)
{
	t_shell	*sh;
	char	*match;
	int		i;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		match = ft_strnstr(sh->env[i], var_name, ft_strlen(var_name));
		if (match)
			return (ft_strchr(match, '=') + CH_SZ);
		i++;
	}
	return (NULL);
}

//var_name format must be 'VAR='
void	set_evar(char *var_name, char *value)
{
	t_shell	*sh;
	size_t	i;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		if (ft_strnstr(sh->env[i], var_name, ft_strlen(var_name)))
		{
			sh->env[i] = sh_guard(ft_strjoin(var_name, value), sh->env[i]);
			return ;
		}
		i++;
	}
	sh->env = sh_ralloc(sh->env, (i + NEW_VAR_SZ + NUL_SZ) * sizeof(char *));
	sh->env[i++] = sh_guard(ft_strjoin(var_name, value), NULL);
	sh->env[i] = NULL;
}

//var_name format must be 'VAR='
void	unset_evar(char *var_name)
{
	t_shell	*sh;
	size_t	i;
	size_t	j;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		if (ft_strnstr(sh->env[i], var_name, ft_strlen(var_name)))
		{
			sh_free(&sh->env[i]);
			j = i;
			while (sh->env[j])
			{
				sh->env[j] = sh->env[j + 1];
				j++;
			}
			sh->env = sh_ralloc(sh->env, (j - NEW_VAR_SZ) * sizeof(char *));
			sh->env[j] = NULL;
			return ;
		}
		i++;
	}
}

void	new_env(t_shell *sh, char **sys_env)
{
	char	**env;
	size_t	count;
	size_t	i;
	t_list	arg;
	t_token	tkn;

	count = 0;
	i = 0;
	while (sys_env[count])
		count++;
	env = sh_calloc(count, sizeof(char *));
	while (i < count)
	{
		env[i] = sh_calloc(ft_strlen(sys_env[i]) + NUL_SZ, sizeof(char));
		ft_memcpy(env[i], sys_env[i], ft_strlen(sys_env[i]) + NUL_SZ);
		i++;
	}
	env[i] = NULL;
	sh->env = env;
	set_prompt();
	tkn.str = "?=0";
	arg = (t_list){&tkn, NULL};
	__export(&arg);
}
