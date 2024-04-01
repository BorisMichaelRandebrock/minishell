/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeppln.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:41:32 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 13:07:24 by fmontser         ###   ########.fr       */
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

static void	_lfreerdrs(t_list *rdrs)
{
	t_list	*prev;
	t_rdr	*rdr;

	while (rdrs)
	{
		rdr = rdrs->content;
		_freerdr(rdr);
		prev = rdrs;
		rdrs = rdrs->next;
		sh_free(&prev);
	}
}

static void	_freerdr(t_rdr *rdr)
{
	_lfreeargs(rdr->args);
	sh_free(&rdr);
}

static void	_freecmd(t_cmd *cmd)
{
	_lfreeargs(cmd->args);
	_lfreerdrs(cmd->rdrs);
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
