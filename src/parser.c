/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/05 19:23:37 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "parser.h"
#include "process.h"
#include "prompt.h"
#include "libft.h"


static void	_destructor(void)
{
	// TODO implement destroyer if needed
}

static bool	_check_bad_args(t_prompt *prompt)
{
	(void)prompt;
	//TODO implementar shell parser (lista de posibles errores de input)
	return (false);
}

static void	_parse_prompt(t_prompt *prompt)
{
	char	*input = prompt->_input;
	size_t	input_sz = ft_strlen(input);
	char	**args;

	if(_check_bad_args(prompt))
		return ;	//TODO shell parse error msg

	args = ft_split(input, ' ');


	if(ft_strncmp(input, "echo", input_sz) == 0)
		printf("echo command recognized!\n");
}

t_parser	new_parser(void)
{
	t_parser	new;

	new.destroy = _destructor;
	new.parse = _parse_prompt;
	return (new);
}
