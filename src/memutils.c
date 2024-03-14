/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/13 19:02:01 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

//Clean exit from shell
void	sh_freexit(int exit_code)
{
	t_shell	*sh;
	size_t	i;

	i = 0;
	sh = get_shell();
	free_env();
	free_shell();
	exit(exit_code);
}
//Protected allocation with calloc
void	*sh_calloc(size_t num, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(num, size);
	if (!alloc)
		sh_perror(MEM_ERROR);
	return (alloc);
}
//Protected reallocation with calloc
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
//Protect allocations, nullable_old free old
void	*sh_guard(void *alloc, void *nullable_old)
{
	if (nullable_old)
		free(nullable_old);
	if (!alloc)
		sh_perror(MEM_ERROR);
	return (alloc);
}


