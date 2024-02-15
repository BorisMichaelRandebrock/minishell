/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/15 17:56:54 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#define QUOTE_SZ 1

// Free process object resources
static void	_destructor(t_prompt *prompt)
{
	if (prompt)
	{
		free(prompt->_input);
		free(prompt);
	}
}

static void	_extract_qs(t_prompt *prompt, char q)
{
	int				i;
	unsigned int	start;
	bool			flag;

	i = 0;
	flag = false;
	while (prompt->_input[i])
	{
		if (prompt->_input[i] == q && !flag)
		{
			flag = !flag;
			start = i;
		}
		else if (prompt->_input[i] == q && flag)
		{
			flag = !flag;
			prompt->_str_list = malloc(sizeof(t_str));
			if (!prompt->_str_list)
				cleanexit(prompt->_shell, MEM_ERROR);
			prompt->_str_list->str = ft_substr(prompt->_input, start, ((i + 1)
						- start));
			prompt->_str_list = prompt->_str_list->next;
		}
		i++;
	}
}

// Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	prompt->_input = readline("🐌 minishell> ");
	add_history(prompt->_input);
	ft_strtrim(prompt->_input, " \\t\\n\\r\\f\\v");
	_extract_qs(prompt, DQU_CH);
	_extract_qs(prompt, SQU_CH);
	// TODO @@@@@@@@ continuar aqui...
}

// Create new process object
t_prompt	*new_prompt(t_shell *shell)
{
	t_prompt	*new;

	new = malloc(sizeof(t_prompt));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	new->_input = NULL; // TODO probar si usando calloc se peude evitar esto.
	new->_shell = shell;
	new->destroy = _destructor;
	new->invoke = _invoker;
	return (new);
}
