/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/29 18:00:50 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	echo hola > file | cat -e > file200


	echo hola | cat -e

	echo > file	// redir exec
	[output (fd)] cat // redir exec



	REDIRS	2			PIPELINES 1
	------				---------
	echo hola			echo hola
	>					|
	file				cat -e

 */


//Creates a cmd sequence and stores it in shell parameters
//TODO esto supone que la lista esta bien pasada




static void	_skip_redirection(t_list *lst)
{
	t_token *tkn;

	tkn = lst->content;
	while ((tkn->type != OP && tkn->optype != PIPE) || lst)
		lst = lst->next;
}

void	get_pipeline(t_list *lst)
{
	t_shell	*sh;
	t_token	*_tkn;
	t_cmd	*cmd;
	t_list	*_lst;

	_lst = lst;
	sh = get_shell();
	while(_lst)
	{
		_tkn = _lst->content;
		if (_tkn->type == CMD)
		{
			cmd = sh_calloc(1, sizeof(t_cmd));
			cmd->cmd = _tkn;
			ft_lstadd_back(&sh->ppln, sh_addfree(ft_lstnew(cmd)));
		}
		else if (_tkn->type == ARG)
			ft_lstadd_back(&cmd->args, sh_addfree(ft_lstnew(_tkn)));
		else if (_tkn->type == OP && _tkn->optype != PIPE)
			_skip_redirection(_lst);
		if (_lst)
			_lst = _lst->next;
	}
}

char	_to_lower(unsigned int ignore, char c)
{
	(void)ignore;
	return (ft_tolower(c));
}

void	exec_pipeline(t_list	*ppln)
{
	static builtin	bif_funcs[7] = {echo, cd, pwd, export, unset, env, exit};
	static char		**bif_names = {"echo,cd,pwd,export,unset,env,exit"};
	char			buff;
	t_cmd	*_cmd;
	int		i;

	i = 0;
	while(ppln)
	{
		_cmd = ppln->content;
		_cmd->cmd->str = sh_addfree(ft_strmapi(_cmd->cmd->str, _to_lower));
		while (bif_names[i])
		{
			buff = bif_names[i];
			if (!ft_strncmp(_cmd->cmd->str, buff,ft_strlen(buff)))
				set_evar("?", sh_addfree(ft_itoa((bif_funcs[i])(_cmd->args))));
		}
		ppln = ppln->next;
	}
}

//TODO el sort debe cumplir todos los modos validos
/*

	//TODO OJO << no funciona a files!!!

	// Pipes entre comandos, derecha a izquierda
	echo test > scpript < file

	// Solo para FD direccion de la redireccion...
	- echo test < file		(fd a encho input)
	- echo test << END		(heredoc a echo input)
	- echo test > file		(echo output a fd overwrite all)
	- echo test >> file		(echo output a fd modo append new line)

	//TODO multiples operadores
	- echo multitest | cat -e > file
	- echo multitest > file | cat -e

	//TODO listar no validos
	- file ? file (cualquier operador entre dos o mas FD)
	- cmd | fd				(pipes con fd)

 */
