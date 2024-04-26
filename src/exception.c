/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:09:41 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/26 15:31:19 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "readline/readline.h"
#include "minishell.h"

//TODO excepcion pipe en primer lugar!
//TODO excepcion, si despues de un pipe no hay nada, se pide input...si...
//TODO excepcion, si un redir no tiene argumento o
// 		el argumento no es valido es un error


//TODO @@@@@@@@@@@@ validar comando y rdin files antes!!!!
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

void	sh_perror(char *error_msg, bool exit)
{
	perror(error_msg);
	if (exit)
		sh_free_exit(FAILURE);
}
