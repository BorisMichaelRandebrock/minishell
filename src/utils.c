/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/19 19:04:52 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

//Clean exit from shell
void	sh_exit(t_shell *shell, int error_code)
{
	if (error_code == MEM_ERROR)
		printf("Memory error, exiting...");
	if (error_code == NULL_ERROR)
		printf("NULL error, exiting...");
	if (shell)
		shell->destroy(shell);
	exit(FAILURE);
}
//Initialize shell first (return null), null shell for use
void	*sh_calloc(t_shell *_nullable_shell, size_t size)
{
	static t_shell	*_shell = NULL;
	void			*new;

	if (!_shell)
	{
		if (!_nullable_shell)
			sh_exit(_nullable_shell, NULL_ERROR);
		_shell = _nullable_shell;
		return (NULL);
	}
	new = ft_calloc(1, size);
	if (!new)
		sh_exit(_nullable_shell, MEM_ERROR);
	return (new);
}

