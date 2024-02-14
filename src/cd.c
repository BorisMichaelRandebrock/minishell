/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:50:43 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/14 15:21:46 by brandebr         ###   ########.fr       */
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
