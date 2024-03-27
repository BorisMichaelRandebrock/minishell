/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/26 14:33:39 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "libfm.h"

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
	while(i >= 0)
	{
		if (buffer[i] == '/')
		{
			i++;
			break ;
		}
		i--;
	}
	prompt = fm_mshld_(ft_strjoin("PROMPT=", &buffer[i]), ex_mem);
	prompt = fm_mshldrw_(ft_strjoin(prompt, " 🐌> "), prompt, ex_mem);
	tkn.str = prompt;
	tkn.type = ARG;
	arg.content = &tkn;
	arg.next = NULL;
	__export(&arg, STDOUT_FILENO);
	free(prompt);
}

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (!shell)
	{
		shell = fm_calloc_(sizeof(t_shell),ex_mem);
		fm_lstapp(&shell->exitlst, shell, ex_mem);
	}
	return (shell);
}

t_shell	*new_shell(char **sys_env)
{
	t_shell	*sh;
	(void)sys_env;
	sh = get_shell();
	new_env(sh, sys_env);
	return (sh);
}
