/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:44:09 by fmontser          #+#    #+#             */
/*   Updated: 2024/02/18 13:09:13 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

//Initialize shell first (return null), null shell for use
void	*sh_calloc(t_shell *_nullable_shell, size_t size)
{
	static t_shell	*_shell = NULL;
	void			*new;

	if (!_shell)
	{
		if (!_nullable_shell)
			cleanexit(_nullable_shell, NULL_ERROR);
		_shell = _nullable_shell;
		return (NULL);
	}
	new = ft_calloc(1, size);
	if (!new)
		cleanexit(_nullable_shell, MEM_ERROR);
	return (new);
}
