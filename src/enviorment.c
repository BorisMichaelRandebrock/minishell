/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:54:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/12 14:10:59 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define	LAST_PROC_DEF		"_="
#define	LAST_EXIT_CODE_DEF	"?="
#define	PATH_DEF			"PATH="
#define	PWD_DEF				"PWD="
#define	OLD_PWD_DEF			"OLDPWD="
#define	TEMP_DIR_DEF		"TMPDIR="

static void	_destroyer(t_env *env)
{
	free(env->last_process_name);
	free(env->last_exit_code);
	free(env->path);
	free(env->pwd);
	free(env->old_pwd);
	free(env->tmp_dir);
	free(env);
}
char	*_get_env_var(char **env, const char *var_def)
{
	int		i;
	char	*buff;

	i = 0;
	while (env[i])
	{
		buff = ft_strnstr(env[i], var_def, ft_strlen(var_def));
		if (buff)
		{
			buff = ft_strdup(buff);
			return (buff);
		}
		i++;
	}
	return (NULL);
}

t_env		*new_enviorment(t_shell *shell, char **env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	*new = (t_env){
		.last_process_name = _get_env_var(env, LAST_PROC_DEF),
		.last_exit_code = NULL,
		.path = _get_env_var(env, PATH_DEF),
		.pwd = _get_env_var(env, PWD_DEF),
		.old_pwd = _get_env_var(env, OLD_PWD_DEF),
		.tmp_dir = _get_env_var(env,TEMP_DIR_DEF)
	};
	new->destroy = _destroyer;
	return (new);
}

//TODO borrar
/*

_=/usr/bin/make				ultimo proceso ejecutado (opcional)
?=0							ultimo codigo de salida recibido
PATH=/bin:/usr/local/bin	Rutas del PATH
PWD=/Users/~/minishell		Directorio actual (.)
OLDPWD=/Users/~				Directorio anterior (..)
TMPDIR=						Directorio temporal (opcional)
 */

/* TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000ccyw00337q/T/
XPC_SERVICE_NAME=0
VSCODE_INJECTION=1
PWD=/Users/fmontser/minishell
MAIL=fmontser@student.42barcelona.com
LSCOLORS=Gxfxcxdxbxegedabagacad
OLDPWD=/Users/fmontser/minishell
LANG=en_US.UTF-8
__CF_USER_TEXT_ENCODING=0x18CF7:0x0:0x0
MAKEFLAGS=s
MFLAGS=-s
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.tdU3FPFsRI/Listeners
ZDOTDIR=/Users/fmontser
ZSH=/Users/fmontser/.oh-my-zsh
MallocNanoZone=0
SHLVL=1
MAKELEVEL=1
PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware Fusion.app/Contents/Public:/usr/local/go/bin:/usr/local/munki
TERM_PROGRAM=vscode
LS_COLORS=di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43
LESS=-R
ORIGINAL_XDG_CURRENT_DESKTOP=undefined
LOGNAME=fmontser
USER_ZDOTDIR=/Users/fmontser
XPC_FLAGS=0x0
USER=fmontser
PAGER=less
_=/usr/bin/make
MAKE_TERMOUT=/dev/ttys001
COLORTERM=truecolor
MAKE_TERMERR=/dev/ttys001
HOME=/Users/fmontser
TERM=xterm-256color
TERM_PROGRAM_VERSION=1.86.0
SHELL=/bin/zsh */
