/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:16:31 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/08 14:21:56 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__exit(t_list *args, int fd)
{
	(void)args;
	(void)fd;
	sh_freexit(SUCCESS);
	return (SUCCESS);
}
