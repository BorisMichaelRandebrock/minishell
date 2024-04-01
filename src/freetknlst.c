/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freetknlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:08:19 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 13:09:13 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	_freetkn(t_token *tkn)
{
	sh_free(&tkn->str);
	sh_free(&tkn);
}

void	sh_lfreetkns(t_list *tkn_lst)
{
	t_list	*prev;
	t_token	*tkn;

	while (tkn_lst)
	{
		tkn = tkn_lst->content;
		_freetkn(tkn);
		prev = tkn_lst;
		tkn_lst = tkn_lst->next;
		sh_free(&prev);
	}
}
