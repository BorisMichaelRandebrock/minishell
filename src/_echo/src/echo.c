/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:26:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/02 17:22:43 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#define NLFLAG "-n"
#define NLFLAG_SIZE 2
#define EQUALS 0

int	main(int argc, char **argv)
{
	int		i;
	char	nl;

	nl = '\n';
	if (argc < 2)
		return (EXIT_FAILURE);
	i = 1;
	if (ft_strncmp(argv[i], NLFLAG, NLFLAG_SIZE) == EQUALS)
	{
		i++;
		nl = '\0';
	}
	while (i < argc)
		printf("%s%c", argv[i++], nl);
	return (EXIT_SUCCESS);
}
