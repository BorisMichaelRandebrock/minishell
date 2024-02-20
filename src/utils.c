/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 13:09:55 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

//Clean exit from shell
void	sh_exit(t_shell *nullable_shell, int error_code)
{
	static t_shell	*_shell = NULL;

	if (!_shell)
	{
		if (!nullable_shell)
			sh_exit(nullable_shell, NULL_ERROR);
		_shell = nullable_shell;
		return ;
	}
	if (error_code == MEM_ERROR)
		printf("Memory error, exiting...");
	if (error_code == NULL_ERROR)
		printf("NULL error, exiting...");
	while (_shell->free_lst)
	{
		free(_shell->free_lst->content);
		_shell->free_lst = _shell->free_lst->next;
	}
	exit(FAILURE);
}
//Initialize shell first (return null), null shell for use
void	*sh_calloc(t_shell *nullable_shell, size_t size)
{
	static t_shell	*_shell = NULL;
	void			*new;

	if (!_shell)
	{
		if (!nullable_shell)
			sh_exit(nullable_shell, NULL_ERROR);
		_shell = nullable_shell;
		return (NULL);
	}
	new = ft_calloc(1, size);
	if (!new)
		sh_exit(nullable_shell, MEM_ERROR);
	if (!_shell->free_lst)
		ft_lstnew(new);
	else
		ft_lstadd_back(&_shell->free_lst, ft_lstnew(new));
	return (new);
}

