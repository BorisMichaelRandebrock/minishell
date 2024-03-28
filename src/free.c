/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:16:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/28 09:32:06 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	sh_free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();

	//TODO free el resto de cosas...
	sh_gfree((void **)&sh);
}

void	sh_free_env(void)
{
	t_shell	*sh;
	size_t	i;

	sh = get_shell();
	i = 0;
	while(sh->env[i])
	{
		sh_gfree((void **)&sh->env[i]);
		i++;
	}
	sh_gfree((void **)&sh->env);
}

















//TODO ESTRUCTURAR!!!! ############

static void _freerdr(t_rdr *rdr);
static void _freecmd(t_cmd *cmd);


static void _lfreeargs(t_list *args)
{
	t_list	*prev;

	while (args)
	{
		prev = args;
		args = args->next;
		sh_gfree((void **)&prev);
	}
}
static void _lfreerdrs(t_list *rdrs)
{
	t_list	*prev;
	t_rdr	*rdr;

	while (rdrs)
	{
		rdr = rdrs->content;
		_freerdr(rdr);
		prev = rdrs;
		rdrs = rdrs->next;
		sh_gfree((void **)&prev);
	}
}

static void _freerdr(t_rdr *rdr)
{
	_lfreeargs(rdr->args);
	sh_gfree((void **)&rdr);
}

static void _freecmd(t_cmd *cmd)
{
	_lfreeargs(cmd->args);
	_lfreerdrs(cmd->rdrs);
	sh_gfree((void **)&cmd);
}

void sh_lfreeppln(t_list *ppln)
{
	t_list	*prev;
	t_cmd	*cmd;

	while (ppln)
	{
		cmd = ppln->content;
		_freecmd(cmd);
		prev = ppln;
		ppln = ppln->next;
		sh_gfree((void **)&prev);
	}
	//TODO abstraer
}











static void _freetkn(t_token *tkn)
{
	sh_gfree((void **)&tkn->str);
	sh_gfree((void **)&tkn);
}

void sh_lfreetkns(t_list *tkn_lst)
{
	t_list	*prev;
	t_token	*tkn;

	while (tkn_lst)
	{
		tkn = tkn_lst->content;
		_freetkn(tkn);
		prev = tkn_lst;
		tkn_lst = tkn_lst->next;
		sh_gfree((void **)&prev);
	}
}










//Clean exit from shell
void	sh_freexit(int exit_code)
{
	t_shell	*sh;
	size_t	i;

	i = 0;
	sh = get_shell();
	sh_free_env();
	sh_free_shell();
	exit(exit_code);
}
