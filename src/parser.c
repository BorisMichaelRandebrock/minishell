/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:34:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/12 20:15:28 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdbool.h>
#include "minishell.h"
#include "libft.h"

#define SPC_CH ' '
#define TAB_CH '\t'
#define SQU_CH '\''
#define DQU_CH '"'
#define MSQ_SPC 0

#define N_TOKEN_TYPES 9

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
	(void) prompt;
	char	*test = "echo \"hola| adios\" si \"seny   or\"cat -e";
	(void) test;
/* masked_split

1. sacar las mascaras con retro-marcado (guardando inicio y usando memset)

						echo "hola|   que" 'tal'"tio"    '  | cat -e
"mask					00000011111111111000000001110000000000000000
'mask					00000000000000000000111000000000000000000000
ch_mask					11110111111000111101111111111000010010111011

2. recorrer y guardar en el heap (char **), no necesita numero previo.
Se van cambiando los modos segun encuentras caracteres quotes u operadores.
Las redirecciones >> se tratan como dos >. (se procesan en otro lado)

mode ch
						echo
mode "	(" & ch)			 hola|   que
mode '	(' & ch)							tal
mode "  (" & ch)							     tio
mode ch													 '
mode op (!(" & ') & ch)										|
mode ch														  cat -e

3. Integrar el array en el parser. */

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
