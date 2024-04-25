/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/25 19:51:24 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

#define DFLT_ENV_SZ 5

void	set_prompt(void)
{
	char	buffer[BUF_1KB];
	char	*prompt;
	int		i;
	t_list	arg;
	t_token	tkn;

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
	prompt = sh_guard(ft_strjoin("PROMPT=", &buffer[i]), NULL);
	prompt = sh_guard(ft_strjoin(prompt, "/::> "), prompt);
	tkn.str = prompt;
	tkn.type = ARG;
	arg.content = &tkn;
	arg.next = NULL;
	__export(&arg);
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
