/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/13 10:42:55 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

void	sh_perror(int error_code)
{
	if (error_code == MEM_ERROR)
		printf("Memory error, exiting...");
	if (error_code == NULL_ERROR)
		printf("NULL error, exiting...");
	sh_freexit(FAILURE);
}

//Clean exit from shell
void	sh_freexit(int exit_code)
{
	t_shell	*sh;
	size_t	i;

	i = 0;
	sh = get_shell();

	//TODO free todo el shell
	while(i < sh->env_sz)
	{
		free(sh->env[i]);
		i++;
	}
	free(sh->env);

	free(sh);
	exit(exit_code);
}
//Initialize shell first (return null), null shell for use
void	*sh_calloc(size_t num, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(num, size);
	if (!alloc)
		sh_perror(MEM_ERROR);
	return (alloc);
}

void	*sh_ralloc(void *old, size_t new_size)
{
	void	*ralloc;

	if (!old)
		return (sh_calloc(1, new_size));
	if (new_size == 0)
		return (old);
	ralloc = sh_calloc(1, new_size);
	if (!ralloc)
		return (NULL);
	ft_memcpy(ralloc, old, new_size);
	if (old)
		free(old);
	return (ralloc);
}

void	*sh_guard(void *alloc, void *nullable_old)
{
	if (nullable_old)
		free(nullable_old);
	if (!alloc)
		sh_perror(MEM_ERROR);
	return (alloc);
}


