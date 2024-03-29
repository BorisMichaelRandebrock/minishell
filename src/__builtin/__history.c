/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:40:13 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/20 11:43:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

#define C_OPT "-c"

//TODO return errors?
static bool	_c_opt_check(t_token *tkn, t_list **_args)
{
	if (!ft_strncmp(tkn->str, C_OPT, 3))
	{
		*_args = (*_args)->next;
		return (true);
	}
	return (false);
}

//TODO return errors?
int	__history(t_list *args, int fd)
{
	t_list	*_args;
	bool	cflag;

	_args = args;
	cflag = _c_opt_check(_args->content, &_args);
	if (cflag)
	{
		clear_history();
		write(fd, "History file deleted.\n", 23);
		return (SUCCESS);
	}
	return (SUCCESS);
}


