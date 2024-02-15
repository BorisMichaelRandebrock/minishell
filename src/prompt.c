/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/15 23:21:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell.h"
#include "libft.h"
#include <string.h>

#define QUOTE_SZ 1
#define DELIMS	"\"\' "

//Free process object resources
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
	(void)prompt;
	//prompt->_input = readline("minishell> ");
	//prompt->_input = ft_strdup("    \"\" echo \"hola ' que\" echo2 'bu'  \"bubu \"    echo3 'ase \" tu'  'por \" aqui' \"nada\"'nada'   echo4   ");
	prompt->_input = ft_strdup("h q");
	toklst(prompt, "\"' ");
	//TODO @@@@@@@ continuar aqui! no coge el ultimo token?¿?¿¿

	t_list *test = prompt->_raw_list;

 	while (test)
	{
		printf("%s\n", test->content);
		test = test->next;
	}
	prompt->destroy(prompt);
	exit(0);

}

//Create new process object
t_prompt	*new_prompt(t_shell *shell)
{
	t_prompt	*new;

	new = malloc(sizeof(t_prompt));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	new->_input = NULL;	//TODO probar si usando calloc se peude evitar esto.
	new->_shell = shell;
	new->destroy = _destructor;
	new->invoke = _invoker;
	return (new);
}
