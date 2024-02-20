/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/20 21:12:40 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	print_error(int error_code)
{
	if (error_code == MEM_ERROR)
		printf("Memory error, exiting...");
	if (error_code == NULL_ERROR)
		printf("NULL error, exiting...");
}

//Clean exit from shell
void	sh_exit(t_shell *nullable_shell)
{
	static t_shell	*_shell = NULL;

	if (!_shell)
	{
		if (!nullable_shell)
			print_error(NULL_ERROR);
		_shell = nullable_shell;
		return ;
	}
	while (_shell->free_cnt->next)
	{
		free(_shell->free_cnt->content);
		_shell->free_cnt = _shell->free_cnt->next;
	}
	while (_shell->free_lst->next)
	{
		free(_shell->free_lst->content);
		_shell->free_lst = _shell->free_lst->next;
	}
	free(_shell->free_lst->content);
	exit(SUCCESS);
}
//Initialize shell first (return null), null shell for use
void	*sh_calloc(t_shell *nullable_shell, size_t size, t_flst list_type)
{
	static t_shell	*_shell = NULL;
	void			*new;
	t_list			*freelst;

	if (!_shell)
	{
		if (!nullable_shell)
			sh_exit(nullable_shell);
		_shell = nullable_shell;
		return (NULL);
	}
	freelst = _shell->free_lst;
	if (list_type == CNT)
		freelst = _shell->free_cnt;
	new = ft_calloc(1, size);
	if (!new)
	{
		print_error(MEM_ERROR);
		sh_exit(nullable_shell);
	}
	if (!freelst)
		ft_lstnew(new);
	else
		ft_lstadd_back(&freelst, ft_lstnew(new));
	return (new);
}

