/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:49:46 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/06 21:22:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





void	build_commands(t_list *tknlst, t_list **ppln)
{
	t_cmd	*cmd;
	(void)ppln;
	while (tknlst)
	{
		cmd = sh_calloc(1, sizeof(t_cmd));
		tknlst = tknlst->next;
	}
}
