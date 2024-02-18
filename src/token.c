/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:37 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/18 14:07:22 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#define EQUALS 0

static void _destructor(t_token *token)
{
	while (token)
	{
		free(token);
	}
}

static t_op	_get_op_type(char *text)
{
	if (ft_strncmp(text, ">", 1) == EQUALS)
		return (RD_OUT);
	else if (ft_strncmp(text, "<", 1) == EQUALS)
		return (RD_IN);
	else if (ft_strncmp(text, ">>", 2) == EQUALS)
		return (RD_OUT_APP);
	else if (ft_strncmp(text, "<<", 2) == EQUALS)
		return (RD_IN_S);
	else if (ft_strncmp(text, "|", 1) == EQUALS)
		return (PIPE);
	return (NONE);
}

t_token	*new_token()
{
	t_token *new;

	new = sh_calloc(NULL,sizeof(t_token));
	new->_type = sh_calloc(NULL,sizeof(t_tokentype));
	new->_op = sh_calloc(NULL, sizeof(t_op));
	new->destroy = _destructor;
	new->get_op_type = _get_op_type;
	return (new);
}
