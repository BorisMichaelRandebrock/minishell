/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:45:27 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 20:30:55 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

static void	_to_sbuffer(t_list *args, char *sbuffer)
{
	t_list	*_args;
	t_token	*_tkn;
	int		i;

	i = 0;
	_args = args->next;
	i += ft_strlen(sbuffer);
	while (_args)
	{
		sbuffer[i++] = ' ';
		_tkn = _args->content;
		ft_memcpy(&sbuffer[i], _tkn->str, ft_strlen(_tkn->str) + NUL_SZ);
		i += ft_strlen(_tkn->str);
		_args = _args->next;
	}
}

static void	_to_file(t_list *args, char *sbuffer, int fd)
{
	t_list	*_args;
	t_token	*_tkn;
	int		i;

	i = 0;
	_args = args->next;
	while (sbuffer[i])
		write(fd, &sbuffer[i++], 1);
	while (_args)
	{
		write(fd, " ", 1);
		_tkn = _args->content;
		write(fd, _tkn->str, ft_strlen(_tkn->str));
		_args = _args->next;
	}
}

//TODO gestionar errores open!!
static void	_rdout(t_list *rdrs, char *sbuffer, int option)
{
	t_rdr	*_rdr;
	t_list	*_args;
	t_token	*_tkn;
	int		fd;

	_rdr = rdrs->content;
	_args = _rdr->args;
	_tkn = _args->content;
	fd = open(_tkn->str, O_WRONLY | O_CREAT | option, 0777);
	if (rdrs->next)
		_to_sbuffer(_args, sbuffer);
	else
		_to_file(_args, sbuffer, fd);
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
