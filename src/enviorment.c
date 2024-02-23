/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/23 19:22:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define	LAST_PROC_DEF	"_="
#define	LAST_EXIT_DEF	"?="
#define	PATH_DEF		"PATH="
#define	PWD_DEF			"PWD="
#define	OLD_PWD_DEF		"OLDPWD="
#define	TEMP_DIR_DEF	"TMPDIR=tmp/"
#define EXIT_DEF_SZ		4

char	*get_env_var(char **env, const char *var_def)
{
	int		i;
	size_t	match_sz;
	char	*match;
	char	*var;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		match = ft_strnstr(env[i], var_def, ft_strlen(var_def));
		if (match)
		{
			match_sz = ft_strlen(match) + NUL_SZ;
			var = sh_calloc(1, match_sz);
			ft_strlcpy(var, match, match_sz);
			return (var);
		}
		i++;
	}
	return (NULL);
}

t_env		*new_env(char **env)
{
	t_env	*new;

	new = sh_calloc(1, sizeof(t_env));
	new->sys_env = env;
	new->path = get_env_var(env, PATH_DEF);
	new->pwd = get_env_var(env, PWD_DEF);
	new->old_pwd = get_env_var(env, OLD_PWD_DEF);
	new->tmp_dir = get_env_var(env, TEMP_DIR_DEF);
	new->last_proc = get_env_var(env, LAST_PROC_DEF);
	new->last_exit = sh_calloc(1, EXIT_DEF_SZ);
	ft_strlcpy(new->last_exit, "?=0", EXIT_DEF_SZ);
	return (new);
}
