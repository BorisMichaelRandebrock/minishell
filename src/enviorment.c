/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/19 17:15:49 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <string.h>

#define NEW_VAR_SZ		1

void	free_env(void)
{
	t_shell	*sh;
	size_t	i;

	sh = get_shell();
	i = 0;
	while(sh->env[i])
	{
		free(sh->env[i]);
		i++;
	}
	free(sh->env);
}

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
	sh->env[i] = NULL; //TODO suspicious...
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
		if (ft_strnstr(sh->env[i], var_name, ft_strlen(var_name) + NUL_CH))
		{
			free(sh->env[i]);
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
	size_t	var_sz;
	size_t	i;
	t_list args;

	i = 0;
	env = sh_calloc(1, sizeof(char *));
	while (sys_env[i])
	{
		var_sz = ft_strlen(sys_env[i]);
		env = sh_ralloc(env, (i + NEW_VAR_SZ) * sizeof(char *));
		env[i] = sh_calloc(var_sz + NUL_SZ, sizeof(char));
		ft_memcpy(env[i], sys_env[i], var_sz);
		i++;
	}
	sh->env = env;
	args.content = &(t_token){ .str = "?=0", .type = ARG};
	args.next = NULL;
	__export(&args, 0);
}
