/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sterm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:37 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/08 16:31:27 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sterm.h"
#include "libft.h"
#define EQUALS 0

static void _destructor(t_sterm *context)
{
	free(context);
}

static t_stermtype	_get_type(char *term)
{
	size_t term_sz;

	term_sz = ft_strlen(term);
	if (ft_strncmp(term, ">", term_sz) == EQUALS)
		return (RD_OUT);
	else if (ft_strncmp(term, "<", term_sz) == EQUALS)
		return (RD_IN);
	else if (ft_strncmp(term, ">>", term_sz) == EQUALS)
		return (RD_OUT_APP);
	else if (ft_strncmp(term, "<<", term_sz) == EQUALS)
		return (RD_IN_S);
	else if (ft_strncmp(term, "|", term_sz) == EQUALS)
		return (PIPE);
	else if (ft_strncmp(term, "$", term_sz) == EQUALS)
		return (VAR);
	else
		return (TEXT);
}

t_sterm	*new_sterm()
{
	t_sterm *new;

	new = malloc(sizeof(t_sterm));
	new->prev = NULL;
	new->next = NULL;
	new->destroy = _destructor;
	new->get_type = _get_type;
	return (new);
}
