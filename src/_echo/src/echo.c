/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:26:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/06 12:53:43 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#define NLFLAG "-n"
#define NLFLAG_SIZE 2
#define EQUALS 0

int	main(int argc, char **argv)
{
	int	i;
	int	nl_flag;

	// char	nl;
	// nl = '\n';
	nl_flag = 1;
	if (argc < 2)
		return (EXIT_FAILURE);
	i = 1;
	if (ft_strncmp(argv[i], NLFLAG, NLFLAG_SIZE) == EQUALS)
	{
		i++;
		nl_flag = 0;
		// nl = '\0';
	}
	while (i < argc)
	{
		printf("%s", argv[i++]);
		if (i < argc)
			printf(" ");
	}
	if (nl_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
