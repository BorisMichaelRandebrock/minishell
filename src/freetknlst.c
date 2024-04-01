/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freetknlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:08:19 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 17:46:29 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	_freetkn(t_token *tkn)
{
	sh_free(&tkn->str);
	sh_free(&tkn);
}

void	sh_lfreetkns(t_list *tknlst)
{
	t_list	*prev;
	t_token	*tkn;

	while (tknlst)
	{
		tkn = tknlst->content;
		_freetkn(tkn);
		prev = tknlst;
		tknlst = tknlst->next;
		sh_free(&prev);
	}
}
