/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/15 20:29:13 by fmontser         ###   ########.fr       */
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
	if (prompt)
	{
		free(prompt->_input);
		free(prompt);
	}
}

static int _extract_token(t_prompt *prompt, int start, int end)
{
	char *token;

	token = ft_substr(prompt->_input, start, ++end - start);
	ft_memmove(&prompt->_input[start], &prompt->_input[end], ft_strlen(prompt->_input) + NUL_CH);
	if (!prompt->_str_list)
		prompt->_str_list = ft_lstnew(token);
	else
		ft_lstadd_back(&prompt->_str_list, ft_lstnew(token));
	return (start);
}

static void _tokenize(t_prompt *prompt, char *dlmt)
{
	int		i;
	int		j;
	int		start;
	int		end;
	bool	flag;
	char	_dlmt;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	flag = false;
	_dlmt = '\0';
	while (prompt->_input[i])
	{
		while (dlmt[j] && !flag)
		{
			if (prompt->_input[i] == dlmt[j])
			{
				_dlmt = dlmt[j];
				break ;
			}
			j++;
		}
		if (prompt->_input[i] == _dlmt)
		{
			flag = !flag;
			if (flag)
				start = i;
			else
				end = i;
			if (start < end && !flag)
			{
				i = _extract_token(prompt, start, end);
				continue ;
			}
		}
		j = 0;
		i++;
	}
	prompt->_split = ft_split(prompt->_input, SPC_CH);
	free(prompt->_input);
	while (*prompt->_split)
	{
		prompt->_input = *prompt->_split;
		_extract_token(prompt, 0, ft_strlen(prompt->_input));
		prompt->_split++;
	}
}



//Invoke a new prompt for input
static void	_invoker(t_prompt *prompt)
{
	(void)prompt;
	//prompt->_input = readline("minishell> ");
	prompt->_input = ft_strdup("    \"\" echo \"hola ' que\" echo2 'bu'  \"bubu \"    echo3 'ase \" tu'  'por \" aqui' \"nada\"'nada'   echo4   ");
	_tokenize(prompt, "\"' ");

	while (prompt->_str_list)
	{
		printf("%s\n", prompt->_str_list->content);
		prompt->_str_list = prompt->_str_list->next;
	}
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
