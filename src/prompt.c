/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/16 09:46:36 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#define QUOTE_SZ 1
#define DELIMS	"\"\' "

// Free process object resources
static void	_destructor(t_prompt *prompt)
{
	t_list	*prev_str;

	if (prompt)
	{
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


//Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	prompt->_input = readline("minishell> ");
	toklst(prompt, "\"' ");
	//TODO @@@@@@@ continuar aqui! intentar romper!

	t_list *test = prompt->_raw_list;

 	while (test)
	{
		printf("%s\n", test->content);
		test = test->next;
	}
	prompt->destroy(prompt);
	exit(0);
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
