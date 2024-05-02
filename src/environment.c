/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/02 18:05:55 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IDX_OFFSET	1
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

void	unset_evar(char *var_name)
{
	t_shell	*sh;
	void	*target;
	int		i;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		if (ft_strnstr(sh->env[i], var_name, ft_strlen(var_name)))
		{
			target = sh->env[i];
			while (sh->env[i])
			{
				sh->env[i] = sh->env[i + 1];
				i++;
			}
			sh->env[i] = NULL;
			sh->env = sh_ralloc(sh->env, ((i + IDX_OFFSET) * sizeof(char *)));
			sh_free(&target);
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
	set_evar("?=", "0");
}
