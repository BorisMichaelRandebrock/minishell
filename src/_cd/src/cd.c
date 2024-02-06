/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:39:38 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/06 18:00:27 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int argc, char **argv)
{
	char	**args;

	args = ft_split(argv[1], ' ');
	if (chdir(args[0]) == -1)
		printf("cd: no such file or directory: %s\n", args[0]);
	else
		printf("changing directory to: %s\n", args[0]);
	/*if (args[1] == NULL)
	{
		if (chdir(args[0]) == -1)
			printf("cd: no such file or directory: %s\n", args[0]);
		else
			printf("changing directory to: %s\n", args[0]);
	}
	else
		printf("changing directory to: %s\n", args[0]);*/
	return (0);
}
