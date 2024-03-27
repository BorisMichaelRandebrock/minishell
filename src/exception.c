/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:24:17 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/25 12:55:32 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	ex_mem(void* ex_arg)
{
	(void)ex_arg;
	printf("%s\n", "MEMORY ERROR: Exiting...");
	sh_freexit(FAILURE);
}

void	ex_perror(void *error_msg)
{
	printf("%s\n", (char *)error_msg);
	sh_freexit(FAILURE);
}
