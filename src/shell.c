/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 14:07:41 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "fm_memory.h"
#include "fm_lists.h"
#include "fm_string.h"
#include "libft.h"

#define DFLT_ENV_SZ 5

void	set_prompt(void)
{
	char	buffer[BUF_1KB];
	char	*prompt;
	int		i;
	t_list	arg;
	t_token	tkn;

	getcwd(buffer, BUF_1KB);
	i = fm_strlen(buffer);
	while(i >= 0)
	{
		if (buffer[i] == '/')
		{
			i++;
			break ;
		}
		i--;
	}
	prompt = sh_guard(ft_strjoin("PROMPT=", &buffer[i]), NULL);
	prompt = sh_guard(ft_strjoin(prompt, " 🐌> "), prompt);
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
		shell = fm_calloc_(sizeof(t_shell),sh_perror, MEM_ERROR);
		fm_lstnew_(shell, shell->exitlst, O_CREATE);
	}
	return (shell);
}

t_shell	*new_shell(char **sys_env)
{
	t_shell	*sh;

	sh = get_shell();
	new_env(sh, sys_env);
	return (sh);
}
