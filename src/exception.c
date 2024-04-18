/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:09:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/18 14:12:14 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

bool	sh_cmd_validation(t_list *ppln, t_list *tknlst)
{
	t_cmd	*cmd;

	cmd = ppln->content;
	if (!cmd->tkn)
	{
		sh_lfreeppln(ppln);
		sh_lfreetkns(tknlst);
		return (false);
	}
	return (true);
}

void	sh_perror(int error_code)
{
	if (error_code == MSH_MERROR)
		printf("Memory error, exiting...");
	if (error_code == MSH_NULLERROR)
		printf("NULL error, exiting...");
	sh_freexit(FAILURE);
}
