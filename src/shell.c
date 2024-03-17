/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:44 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/17 18:57:29 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

#define DFLT_ENV_SZ 5

void	set_prompt(void)
{
	t_list	args;
	char	buffer[BUF_1KB];
	char	*prompt;
	int		i;

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
	prompt = sh_guard(ft_strjoin("PROMPT=", &buffer[i]), NULL);
	prompt = sh_guard(ft_strjoin(prompt, " 🐌> "), prompt);
	args.content = &(t_token){ .str = prompt, .type = ARG};
	args.next = NULL;
	__export(&args, 0);
	free(prompt);
}

void	free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();

	//TODO free el resto de cosas...
	free(sh);
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
	new_env(sh, sys_env, &sh->env_sz);
	set_prompt();
	return (sh);
}
