/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:18:42 by fmontser          #+#    #+#             */
/*   Updated: 2024/05/17 16:13:21 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

#define NUL_FD		-1

bool	process_rd_in(t_list *rdrs_in, int pp_wr)
{
	t_token	*_rdr;

	while (rdrs_in)
	{
		_rdr = rdrs_in->content;
		if (!validate_rdrin(_rdr))
			return (false);
		if (_rdr->type == RDIN && !rdrs_in->next)
			sh_fprelay(_rdr->str, pp_wr);
		else if (_rdr->type == RDHDOC)
		{
			if (!rdrs_in->next)
				invoke_heredoc(_rdr->str, pp_wr);
			else
				invoke_heredoc(_rdr->str, NUL_FD);
		}
		rdrs_in = rdrs_in->next;
	}
	return (true);
}

bool	process_rd_out(t_list *rdrs_out)
{
	t_token	*_rdr;
	int		fd;

	while (rdrs_out)
	{
		_rdr = rdrs_out->content;
		if (!validate_rdrout(_rdr))
			return (false);
		if (_rdr->type == RDOUT)
			fd = open(_rdr->str, O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (_rdr->type == RDAPP)
			fd = open(_rdr->str, O_APPEND | O_CREAT | O_RDWR, 0777);
		rdrs_out = rdrs_out->next;
	}
	dup2(fd, STDOUT_FILENO);
	return (true);
}

bool	process_rd_out_empty(t_list *rdrs_out)
{
	t_token	*_rdr;
	int		fd;

	while (rdrs_out)
	{
		_rdr = rdrs_out->content;
		if (!validate_rdrout(_rdr))
			return (false);
		if (_rdr->type == RDOUT)
			fd = open(_rdr->str, O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (_rdr->type == RDAPP)
			fd = open(_rdr->str, O_APPEND | O_CREAT | O_RDWR, 0777);
		rdrs_out = rdrs_out->next;
	}
	return (true);
}
