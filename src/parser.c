/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/13 13:49:29 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "minishell.h"
#include "libft.h"


#define N_TOKEN_TYPES 9 //TODO es necesario?

//Free process object resources
static void	_destructor(t_parser *parser)
{
	int	i;

	i = 0;
	while(parser->_split[i])
	{
		free(parser->_split[i]); //TODO check leaks!
		i++;
	}
}





//Parse user input via prompt object
static void	_parse_prompt(t_prompt *prompt)
{
	(void)prompt;
/*
	int		i;
	int		j;
	bool	tflag;
	char	*token_ptr;
	char	*split_lst;

 	split_lst = prompt->_shell->_parser->_split;
	split_lst = malloc(sizeof(char **));	//TODO pasar al inicializador parser
	if (!split_lst)
		cleanexit(prompt->_shell, MEM_ERROR);


//TODO pre-clean whitespace!!!!

	i = 0;
	j = 0;
	tflag = false;
	while (prompt->_input[i])
	{
		if ((prompt->_dq_mask[i] == '0' && prompt->_sq_mask[i] == '0')) //Si no hay mascaras
		{
			if (prompt->_input[i] != SPC_CH && !tflag)	// si no hay espacio y tflag es falso
			{
				token_ptr = &prompt->_input[i];	// Guarda el token_ptr
				tflag = true;
			}
			else if (prompt->_input[i] == SPC_CH && tflag) // si hay un espacio y tflag es true
			{
				split_lst[j] = ft_calloc(  , sizeof(char));
			}
		}


		//if (prompt->_dq_mask[i] == '1' || prompt->_sq_mask[i] == '1')
	}
 */


	printf("%s\n", prompt->_input);
	printf("%s\n", prompt->_dq_mask);
	printf("%s\n", prompt->_sq_mask);
}

//Create new process object
t_parser	*new_parser(t_shell *shell)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		cleanexit(shell, MEM_ERROR);
	new->_shell = shell;
	new->destroy = _destructor;
	new->parse = _parse_prompt;
	return (new);
}
