/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/19 19:09:51 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#define QUOTE_SZ 1
#define DELIMS "\"\' "

// Free process object resources
static void	_destructor(t_prompt *prompt)
{
	t_list	*prev_str;

	if (prompt)
	{
		if (prompt->_input)
			free(prompt->_input);
		while (prompt->_raw_list)
		{
			free(prompt->_raw_list->content);
			prev_str = prompt->_raw_list;
			prompt->_raw_list = prompt->_raw_list->next;
			free(prev_str);
		}
		free(prompt);
	}
}

static void	_invoker(t_prompt *prompt)
{

	//TODO @@@@@@@ tokeniza a comandos. dede el prompt directo.
	// Establecer la logica CMD > ARG > OP ? OP ?

	prompt->_input = ft_strdup("echo\"hola '     \"'que  \"  ' ");
	//prompt->_input = readline("🐌 minishell> ");

	exit(0);
}

// Create new process object
t_prompt	*new_prompt(t_shell *shell)
{
	t_prompt	*new;

	new = sh_calloc(NULL, sizeof(t_prompt));
	new->_shell = shell;
	new->destroy = _destructor;
	new->invoke = _invoker;
	return (new);
}
