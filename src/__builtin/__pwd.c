/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:29:40 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/04 16:51:36 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include "minishell.h"

//TODO return errors?
int	__pwd(t_list *args, int fd)
{
	(void)args;
	t_list lst;
	t_token tkn;

	tkn.str = get_evar("PWD");
	tkn.type = ARG;
	lst.content = &tkn;
	__echo(&lst,fd);
	return(SUCCESS);
}
