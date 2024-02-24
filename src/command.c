/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/24 14:12:00 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO el sort debe cumplir todos los modos validos
/*

	// Pipes entre comandos, derecha a izquierda
	echo test | cat -e

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


void	sort_sequence(t_list *cmd_lst)
{
	(void)cmd_lst;
	//TODO establecer el orden de ejecucion adecuado
	//TODO usar recursion para stackear soluciones?
	//TODO crear una lista y alternarn entre lst_front y lst_end para alterar el orden?..
}

//Creates a cmd sequence and stores it in shell parameters
void	sequence_cmd(t_shell *sh, t_list *tkn_lst)
{
	t_token	*tkn;
	t_cmd	*cmd;

	cmd = sh_calloc(1, sizeof(t_cmd));
	while(tkn_lst)
	{
		tkn = tkn_lst->content;
		if (tkn->type == CMD)
			cmd->name = tkn;
		else if (tkn->type == ARG)
			ft_lstadd_back(&cmd->args, sh_addfree(ft_lstnew(tkn)));
		else if (tkn->type == OP)
		{
			ft_lstadd_back(&sh->cmd_lst, sh_addfree(ft_lstnew(cmd)));
			cmd = sh_calloc(1, sizeof(t_cmd));
			cmd->name = tkn;
			ft_lstadd_back(&sh->cmd_lst, sh_addfree(ft_lstnew(cmd)));
			if (tkn_lst->next)
				sequence_cmd(sh, tkn_lst->next);
			return ;
		}
		tkn_lst = tkn_lst->next;
	}
	ft_lstadd_back(&sh->cmd_lst, sh_addfree(ft_lstnew(cmd)));
}

