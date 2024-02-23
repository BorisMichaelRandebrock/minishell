/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:50:43 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/23 14:34:04 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_prompt *prompt)
{
	char	*path;

	path = ft_split(prompt->_input);
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
	}
	else
		printf("cd: %s", getenv("PWD"));
	free(path);
	return (SUCCESS);
}
