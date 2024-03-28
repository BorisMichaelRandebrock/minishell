/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:45:27 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/28 11:21:34 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void	_rdout(t_list *rdrs, char *shell_buffer, int option)
{
	t_rdr	*_rdr;
	t_list	*_args;
	t_token	*_tkn;
	int	fd;
	int	i;

	i = 0;
	_rdr = rdrs->content;
	_args = _rdr->args;
	_tkn = _args->content;
	fd = open(_tkn->str, O_WRONLY | O_CREAT | option, 0777); //TODO gestionar errores open!!
	if (rdrs->next)
	{
		_args = _args->next;
		i += ft_strlen(shell_buffer);
		while (_args)
		{
			shell_buffer[i++] = ' ';
			_tkn = _args->content;
			ft_memcpy(&shell_buffer[i], _tkn->str, ft_strlen(_tkn->str) + NUL_SZ);
			i += ft_strlen(_tkn->str);
			_args = _args->next;
		}
	}
	else
	{
		while(shell_buffer[i])
			write(fd, &shell_buffer[i++], 1);
		_args = _args->next;
		while (_args)
		{
			write(fd, " ", 1);
			_tkn = _args->content;
			write(fd, _tkn->str, ft_strlen(_tkn->str));
			_args = _args->next;
		}
	}
	close(fd);
}

//TODO gestionar errores open??
void	process_redirs(t_list *rdrs, char *shell_buffer)
{
	t_rdr	*_rdr;

	while (rdrs)
	{
		_rdr = rdrs->content;
		if (_rdr->op->type == RDOUT)
			_rdout(rdrs, shell_buffer, O_TRUNC);
		else if (_rdr->op->type == RDAPP)
			_rdout(rdrs, shell_buffer, O_APPEND);
		else if (_rdr->op->type == RDIN)
		{
			//TODO cuando hagamos los procesos externoss
		}
		else if (_rdr->op->type == RDHDOC)
		{
			//TODO cuando hagamos los procesos externos
		}
		rdrs = rdrs->next;
	}
	ft_memset(shell_buffer, '\0', BUF_1MB);
}
