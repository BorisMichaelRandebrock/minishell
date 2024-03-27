/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:16:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/27 21:16:41 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/* static void	_shldfree(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;	//TODO um...
	}
} */


void	sh_free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();

	//TODO free el resto de cosas...
	free(sh);
}

void	sh_free_env(void)
{
	t_shell	*sh;
	size_t	i;

	sh = get_shell();
	i = 0;
	while(sh->env[i])
	{
		free(sh->env[i]);
		i++;
	}
	free(sh->env);
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
		free(prev);
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
		free(prev);
	}
}

static void _freerdr(t_rdr *rdr)
{
	_lfreeargs(rdr->args);
	free(rdr);
}

static void _freecmd(t_cmd *cmd)
{
	_lfreeargs(cmd->args);
	_lfreerdrs(cmd->rdrs);
	free(cmd);
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
		free(prev);
	}
	//TODO abstraer
}











static void _freetkn(t_token *tkn)
{
	free(tkn->str);
	free(tkn);
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
		free(prev);
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
