/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/13 20:25:52 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "minishell.h"
#include "libft.h"

#define QUOTE_SZ 1

//Free process object resources
static void	_destructor(t_prompt *prompt)
{
	if (prompt)
	{
		free(prompt->_input);
		free(prompt->_mask);
		free(prompt);
	}
}

static void	_clean_whitespace(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->_input[i])
	{
		if (ft_is_whspc(prompt->_input[i]) && (prompt->_mask[i] == '0'))
		{
			if (prompt->_input[i] != SPC_CH)
				prompt->_input[i] = SPC_CH;
			while (i > 0 && ft_is_whspc(prompt->_input[i + 1]))
			{
				ft_memmove(&prompt->_input[i], &prompt->_input[i + 1],
					ft_strlen(&prompt->_input[i]));
				ft_memmove(&prompt->_mask[i], &prompt->_mask[i + 1],
					ft_strlen(&prompt->_mask[i]));
			}
		}
		i++;
	}
}

static void	_set_mask(t_prompt *prompt)
{
	char	*mask_ptr;
	bool	qflag;
	int		i;
	int		id;
	char	qchar;

	i = 0;
	id = 1;
	qflag = false;
	while (prompt->_input[i])
	{
		if ((prompt->_input[i] == SQU_CH || prompt->_input[i] == DQU_CH)
			&& (i == 0 || qflag == false))
			qchar = prompt->_input[i];
		if (prompt->_input[i] == qchar)
		{
			qflag = !qflag;
			if (qflag)
				mask_ptr = &prompt->_mask[i];
			else
				ft_memset(mask_ptr, ('0' + id++),
					(&prompt->_mask[i] - mask_ptr) + QUOTE_SZ);
		}
		i++;
	}
}

//Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	char	*mask;

	prompt->_input = readline("minishell> ");
	add_history(prompt->_input);
	prompt->_size = ft_strlen(prompt->_input);
	mask = ft_calloc(prompt->_size + NUL_SZ, sizeof(char));
	if (!mask)
		cleanexit(prompt->_shell, MEM_ERROR);
	ft_memset(mask, '0', prompt->_size);
	prompt->_mask = mask;
	_set_mask(prompt);
	_clean_whitespace(prompt);
	printf("%s\n", prompt->_input);
	printf("%s\n", prompt->_mask);
	prompt->_size = ft_strlen(prompt->_input);
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
