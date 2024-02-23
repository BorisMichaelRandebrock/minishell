/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:36:51 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/15 17:55:57 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*pwd;

	// pwd = getenv("PWD");
	pwd = getcwd(NULL, sizeof(char *));
	if (pwd)
		printf("%s\n", pwd);
	else
		printf("error retrieving current directory: getcwd: cannot access "
				"parent directories: No such file or directory\n");
	free(pwd);
	return (SUCCESS);
}
