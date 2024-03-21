/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:45:27 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/21 16:35:22 by fmontser         ###   ########.fr       */
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
	int		fd;
	int		i;

	while (cmd->rdrs)
	{
		rdr = cmd->rdrs->content;
		i = 0;
		if (rdr->op->type == RDOUT)
		{
			arg = rdr->args->content;
			fd = open(arg->str, O_WRONLY | O_CREAT | O_TRUNC, 0777); //TODO gestionar errores open??
			if (!cmd->rdrs->next)
				while(shell_buffer[i])
					write(fd, &shell_buffer[i++], 1);
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
			//TODO cuando hagamos los procesos externos
		}
		else if (rdr->op->type == RDHDOC)
		{
			//TODO cuando hagamos los procesos externos
		}
		cmd->rdrs = cmd->rdrs->next;
	}
	ft_memset(shell_buffer, '\0', BUF_1MB);
}
