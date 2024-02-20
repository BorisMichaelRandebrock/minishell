/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 23:27:29 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	sh_perror(int error_code)
{
	if (error_code == MEM_ERROR)
		printf("Memory error, exiting...");
	if (error_code == NULL_ERROR)
		printf("NULL error, exiting...");
	sh_exit(FAILURE);
}

//Clean exit from shell
void	sh_exit(int exit_code)
{
	t_shell	*sh;
	t_list	*next;

	sh = get_shell();
	while (sh->free_lst)
	{
		next = sh->free_lst->next;
		ft_lstdelone(sh->free_lst, free);
		sh->free_lst = next;
	}
	exit(exit_code);
}
//Initialize shell first (return null), null shell for use
void	*sh_calloc(size_t num, size_t size)
{
	t_shell	*sh;
	void	*alloc;

	sh = get_shell();
	alloc = ft_calloc(num, size);
	if (!alloc)
		sh_perror(MEM_ERROR);
	if (!sh->free_lst)
		sh->free_lst = ft_lstnew(alloc);
	else
		ft_lstadd_front(&sh->free_lst, ft_lstnew(alloc));
	return (alloc);
}

void	*sh_addfree(void *alloc)
{
	t_shell	*sh;

	sh = get_shell();
	ft_lstadd_front(&sh->free_lst, ft_lstnew(alloc));
	return (alloc);
}


