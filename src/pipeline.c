/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:26:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/08 18:01:19 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define NUL_SZ	1


/*
	Concepto del los argumentos que destruyen FD amenaza fantasma
	excpecto los argumentos tipo opcion.
	como diferenciar opciones de lo que no son??
*/


void	exec_pipeline(t_list *ppln)
{
	char	sbuffer[BUF_1KB + NUL_SZ];
	t_cmd	*cmd;

	ft_memset(sbuffer, '\0', BUF_1KB + NUL_SZ);
	while (ppln)
	{
		cmd = ppln->content;
		if (ppln->next)
			cmd->to_pipe = true;
		if (try_builtin(cmd, sbuffer) == FAILURE)
			try_process(cmd, sbuffer);
		ppln = ppln->next;
	}
}

