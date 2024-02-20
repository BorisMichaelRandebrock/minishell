/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 12:58:02 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define	LAST_PROC_DEF		"_="
#define	LAST_EXIT_DEF		"?="
#define	PATH_DEF			"PATH="
#define	PWD_DEF				"PWD="
#define	OLD_PWD_DEF			"OLDPWD="
#define	TEMP_DIR_DEF		"TMPDIR="

char	*_get_env_var(char **env, const char *var_def)
{
	int		i;
	size_t	match_sz;
	char	*match;
	char	*var;

	i = 0;
	while (env[i])
	{
		match = ft_strnstr(env[i], var_def, ft_strlen(var_def));
		if (match)
		{
			match_sz = ft_strlen(match) + NUL_SZ;
			var = sh_calloc(NULL, match_sz);
			ft_strlcpy(var, match, match_sz);
			return (var);
		}
		i++;
	}
	return (NULL);
}

t_env		*new_enviorment(char **env)
{
	t_env	*new;

	new = sh_calloc(NULL, sizeof(t_env));
	new->last_proc = _get_env_var(env, LAST_PROC_DEF);
	new->last_exit = sh_calloc(NULL, ft_strlen(LAST_EXIT_DEF) + 1 + NUL_SZ);
	ft_strlcpy(new->last_exit, "?=0", 4);
	new->path = _get_env_var(env, PATH_DEF);
	new->pwd = _get_env_var(env, PWD_DEF);
	new->old_pwd = _get_env_var(env, OLD_PWD_DEF);
	new->tmp_dir = _get_env_var(env, TEMP_DIR_DEF);
	return (new);
}
