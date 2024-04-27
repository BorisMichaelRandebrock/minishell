/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/27 15:01:42 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

bool	is_builtin(char *cmd_name)
{
	static char		*bltn_id[9] = {"echo", "export", "cd", "pwd",
		"unset", "env", "exit", "history", NULL};
	int				i;
	size_t			cmp_sz;

	i = 0;
	while (bltn_id[i])
	{
		cmp_sz = ft_strlen(bltn_id[i]) + NUL_SZ;
		if (!ft_strncmp(cmd_name, bltn_id[i], cmp_sz))
			return (true);
		i++;
	}
	return (false);
}

void	set_prompt(void)
{
	char	buffer[BUF_1KB];
	char	*prompt;
	int		i;

	getcwd(buffer, BUF_1KB);
	i = ft_strlen(buffer);
	while (i >= 0)
	{
		if (buffer[i] == '/')
		{
			i++;
			break ;
		}
		i--;
	}
	prompt = sh_guard(ft_strjoin(&buffer[i], "/::> "), NULL);
	set_evar("PROMPT=", prompt);
	sh_free(&prompt);
}

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (!shell)
		shell = sh_guard(ft_calloc(1, sizeof(t_shell)), NULL);
	return (shell);
}

t_shell	*new_shell(char **sys_env)
{
	t_shell	*sh;

	sh = get_shell();
	sh_init_handlers();
	tcgetattr(STDIN_FILENO, &sh->trmcfgbackup);
	tcgetattr(STDIN_FILENO, &sh->trmcfg);
	sh->trmcfg.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->trmcfg);
	new_env(sh, sys_env);
	return (sh);
}
