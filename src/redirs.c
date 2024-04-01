/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:45:27 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/01 13:26:48 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//TODO exception gestionar errores open!!
static void	_rdout(t_list *rdrs, char *shbuff, int option)
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
	fd = open(_tkn->str, O_WRONLY | O_CREAT | option, 0777);
	if (rdrs->next)
	{
		_args = _args->next;
		i += ft_strlen(shbuff);
		while (_args)
		{
			shbuff[i++] = ' ';
			_tkn = _args->content;
			ft_memcpy(&shbuff[i], _tkn->str, ft_strlen(_tkn->str) + NUL_SZ);
			i += ft_strlen(_tkn->str);
			_args = _args->next;
		}
	}
	else
	{
		while(shbuff[i])
			write(fd, &shbuff[i++], 1);
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
void	process_redirs(t_list *rdrs, char *shbuff)
{
	t_rdr	*_rdr;

	while (rdrs)
	{
		_rdr = rdrs->content;
		if (_rdr->op->type == RDOUT)
			_rdout(rdrs, shbuff, O_TRUNC);
		else if (_rdr->op->type == RDAPP)
			_rdout(rdrs, shbuff, O_APPEND);
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
	ft_memset(shbuff, '\0', BUF_1MB);
}
