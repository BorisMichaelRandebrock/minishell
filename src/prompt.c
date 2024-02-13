/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/13 17:59:58 by fmontser         ###   ########.fr       */
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
		free(prompt);
	}
}

static void	_clean_whitespace(t_prompt *prompt)
{
	int	i;

	i = 0;
	while(prompt->_input[i])
	{
		if (ft_is_whspc(prompt->_input[i]) && (prompt->_dq_mask[i] == '0' && prompt->_sq_mask[i] == '0'))
		{
			if (prompt->_input[i] != SPC_CH)
				prompt->_input[i] = SPC_CH;
			while (i > 0 && ft_is_whspc(prompt->_input[i + 1]))
			{
				ft_memmove(&prompt->_input[i], &prompt->_input[i + 1], ft_strlen(&prompt->_input[i]));
				ft_memmove(&prompt->_dq_mask[i], &prompt->_dq_mask[i + 1], ft_strlen(&prompt->_dq_mask[i]));
				ft_memmove(&prompt->_sq_mask[i], &prompt->_sq_mask[i + 1], ft_strlen(&prompt->_sq_mask[i]));
			}
		}
		i++;
	}
}

static char	*_get_mask(t_prompt *prompt, char c)	//TODO unificar mascaras?
{
	char	*mask_ptr;
	char	*mask;
	bool	qflag;
	int	i;

	mask = ft_calloc(prompt->_size + NUL_SZ, sizeof(char));
	if (!mask)
		cleanexit(prompt->_shell, MEM_ERROR);
	ft_memset(mask, '0', prompt->_size);
	i = 0;
	qflag = false;
	while (prompt->_input[i])
	{
		if(prompt->_input[i] == c)
		{
			qflag = !qflag;
			if (qflag)
				mask_ptr = &mask[i];
			else
				ft_memset(mask_ptr, '1', (&mask[i] - mask_ptr) + QUOTE_SZ);
		}
		i++;
	}
	return (mask);
}


//Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	prompt->_input = readline("minishell> ");
	add_history(prompt->_input);
	prompt->_size = ft_strlen(prompt->_input);
	prompt->_dq_mask = _get_mask(prompt, DQU_CH);
	prompt->_sq_mask = _get_mask(prompt, SQU_CH);
	printf("%s\n", prompt->_input);
	printf("%s\n", prompt->_dq_mask);
	printf("%s\n", prompt->_sq_mask);

	_clean_whitespace(prompt);
	printf("%s\n", prompt->_input);
	exit(0);
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
