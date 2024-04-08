/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeppln.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:41:32 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/08 13:25:44 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	_freerdr(t_rdr *rdr);
static void	_freecmd(t_cmd *cmd);

static void	_lfreeargs(t_list *args)
{
	t_list	*prev;

	while (args)
	{
		prev = args;
		args = args->next;
		sh_free(&prev);
	}
}

static void	_freecmd(t_cmd *cmd)
{
	t_list	*prev;

	_lfreeargs(cmd->args);
	while (cmd->rdrs_in)
	{
		prev = cmd->rdrs_in;
		cmd->rdrs_in = cmd->rdrs_in->next;
		sh_free(&prev);
	}
	while (cmd->rdrs_out)
	{
		prev = cmd->rdrs_out;
		cmd->rdrs_out = cmd->rdrs_out->next;
		sh_free(&prev);
	}
	sh_free(&cmd);
}

void	sh_lfreeppln(t_list *ppln)
{
	t_list	*prev;
	t_cmd	*cmd;

	while (ppln)
	{
		cmd = ppln->content;
		_freecmd(cmd);
		prev = ppln;
		ppln = ppln->next;
		sh_free(&prev);
	}
}
