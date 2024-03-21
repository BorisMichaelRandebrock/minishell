/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:45:27 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/21 18:44:28 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


void	process_redirs(t_cmd *cmd, char *shell_buffer)
{
	t_rdr	*rdr;
	t_token	*arg;
	t_list	*args_list;
	int		fd;
	int		i;
	void	*free_prev;

	while (cmd->rdrs)
	{
		rdr = cmd->rdrs->content;
		args_list = rdr->args;
		i = 0;
		if (rdr->op->type == RDOUT)
		{
			arg = rdr->args->content;
			fd = open(arg->str, O_WRONLY | O_CREAT | O_TRUNC, 0777); //TODO gestionar errores open??
			if (!cmd->rdrs->next)
				while(shell_buffer[i])
					write(fd, &shell_buffer[i++], 1);
				i = 0;
				rdr->args = rdr->args->next;
				while (rdr->args)	//TODO //BUG //FIXME cantidade de LEAKS en los argumentos
				{
					write(fd, " ", 1);
					arg = rdr->args->content;
					write(fd, arg->str, ft_strlen(arg->str));
					rdr->args = rdr->args->next;
				}
			close(fd);
		}
		else if (rdr->op->type == RDAPP)
		{
			arg = rdr->args->content;
			fd = open(arg->str, O_WRONLY | O_CREAT | O_APPEND, 0777); //TODO gestionar errores open??
			while(shell_buffer[i])
				write(fd, &shell_buffer[i++], 1);
			close(fd);
		}
		else if (rdr->op->type == RDIN)
		{
			//TODO cuando hagamos los procesos externoss
		}
		else if (rdr->op->type == RDHDOC)
		{
			//TODO cuando hagamos los procesos externos
		}
		free(args_list);
		free(rdr);
		free_prev = cmd->rdrs;
		cmd->rdrs = cmd->rdrs->next;
		free(free_prev);
	}
	ft_memset(shell_buffer, '\0', BUF_1MB);
}
