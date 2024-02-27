/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/27 15:47:03 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
	char	*_env_var;

	_env_var= sh_addfree(ft_strjoin(var_name, "="));
	sh = get_shell();
	sh->env->_fd = dup(sh->env->fd);
	while (sh->env->_fd)
	{
		match = ft_strnstr(get_next_line(sh->env->_fd),
				_env_var, ft_strlen(_env_var));
		if (match)
			sh->env->_fd = close(sh->env->_fd);
	}
	return (match);
}

static char	*_get_sys_var(char **env, const char *var_def)
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
			var = sh_calloc(1, match_sz);
			ft_strlcpy(var, match, match_sz);
			return (var);
		}
		i++;
	}
	return (NULL);
}

//TODO proteger  y crear wrap para gestionar archivos open, etc...
t_env	*new_env(char **env)
{
	static char	*defs[4] = {PATH_DEF, PWD_DEF, OLD_PWD_DEF, LAST_PROC_DEF};
	char		*var;
	t_env		*new;
	size_t		def_sz;
	size_t		i;

	new = sh_calloc(1, sizeof(t_env));
	new->filename = sh_addfree(ft_strdup("env"));
	new->fd = open(new->filename, O_RDWR | O_APPEND | O_CREAT, 0777);
	new->_fd = dup(new->fd);
	i = 0;
	while (i < 4)
	{
		var = _get_sys_var(env, defs[i]);
		def_sz = ft_strlen(var);
		write(new->_fd, var, def_sz);
		write(new->_fd, NL_STR, CH_SZ);
		i++;
	}
	write(new->_fd, LAST_EXIT_DEF, 2);
	close(new->_fd);
	return (new);
}
