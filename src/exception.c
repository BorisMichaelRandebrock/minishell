/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:24:17 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/06 21:34:18 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	sh_perror(int error_code)
{
	if (error_code == MSH_MERROR)
		printf("Memory error, exiting...");
	if (error_code == MSH_NULLERROR)
		printf("NULL error, exiting...");
	sh_freexit(FAILURE);
}
