/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/28 18:21:01 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define LAST_PROC_DEF	"_="
#define LAST_EXIT_DEF	"?="
#define PATH_DEF		"PATH="
#define PWD_DEF			"PWD="
#define OLD_PWD_DEF		"OLDPWD="

char	*read_env(char *var_name)
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
		{
			match = ft_strchr(match, '=') + CH_SZ;
			match = sh_addfree(ft_strdup(match));
			return (match);
		}
		i++;
	}
	return (NULL);
}

char	**new_env(char **sys_env)
{
	static char	*defs[4] = {PATH_DEF, PWD_DEF, OLD_PWD_DEF, LAST_PROC_DEF};
	size_t		i;
	size_t		j;
	char		*match;
	char		**env;

	env = sh_calloc(5, sizeof(char *));
	i = -1;
	j = -1;
	while (++i < 4)
	{
		while (sys_env[++j])
		{
			match = ft_strnstr(sys_env[j], defs[i], ft_strlen(defs[i]));
			if (match)
			{
				env[i] = sh_addfree(ft_strdup(match));
				break ;
			}
		}
		j = -1;
	}
	env[i] = sh_addfree(ft_strdup(LAST_EXIT_DEF));
	return (env);
}
