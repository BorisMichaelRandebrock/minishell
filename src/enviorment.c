/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 14:54:41 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "libfm.h"

#define NEW_VAR_SZ		1

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
	size_t	rsize;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		if (ft_strnstr(sh->env[i], var_name, ft_strlen(var_name)))
		{
			fm_lstdelnd2(&sh->exitlst, sh->env[i]);
			sh->env[i] = fm_mshld3_(ft_strjoin(var_name, value),ex_mem, &sh->exitlst);
			return ;
		}
		i++;
	}
	rsize = (i + NEW_VAR_SZ + NUL_SZ) * sizeof(char *);
	sh->env = fm_realloc3_(rsize, sh->env, ex_mem, &sh->exitlst);
	fm_lstdelnd2(&sh->exitlst, sh->env[i]);
	sh->env[i] = fm_mshldrw3_(ft_strjoin(var_name, value), sh->env[i], ex_mem, &sh->exitlst);
	sh->env[++i] = NULL;
}

//var_name format must be 'VAR='
void	unset_evar(char *var_name)
{
	t_shell	*sh;
	size_t	i;
	size_t	j;
	size_t	rsize;

	sh = get_shell();
	i = 0;
	while (sh->env[i])
	{
		if (ft_strnstr(sh->env[i], var_name, ft_strlen(var_name)))
		{
			fm_lstdelnd2(&sh->exitlst, sh->env[i]);
			j = i;
			while (sh->env[j])
			{
				sh->env[j] = sh->env[j + 1];
				j++;
			}
			rsize = (j - NEW_VAR_SZ) * sizeof(char *);
			sh->env = fm_realloc3_(rsize, sh->env, ex_mem, &sh->exitlst);
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
	size_t	count;
	size_t	i;
	t_list	arg;
	t_token	tkn;

	count = 0;
	i = 0;
	while (sys_env[count])
		count++;
	env = fm_calloc3_((count + NUL_SZ) * sizeof(char *),ex_mem, &sh->exitlst);
	while (i < count)
	{
		var_sz = ft_strlen(sys_env[i]);
		env[i] = fm_calloc3_(var_sz + NUL_SZ * sizeof(char), ex_mem, &sh->exitlst);
		ft_memcpy(env[i], sys_env[i], var_sz + NUL_SZ);
		i++;
	}
	env[i] = NULL;
	sh->env = env;
	set_prompt();
 	tkn.str = "?=0";
	arg.content = &tkn;
	arg.next = NULL;
	__export(&arg, STDOUT_FILENO);
}
