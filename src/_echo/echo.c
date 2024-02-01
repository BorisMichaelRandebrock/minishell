/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:26:08 by brandebr          #+#    #+#             */
/*   Updated: 2024/02/01 19:12:28 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#define NLFLAG "-n"
#define NLFLAG_SIZE 2
#define EQUALS 0

static int	_cmp_result(const char *s1, const char *s2);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 1;
	if (n == 0)
	{
		return (0);
	}
	while (*s1 && (*s1 == *s2))
	{
		if (count >= n)
		{
			return (_cmp_result(s1, s2));
		}
		s1++;
		s2++;
		count++;
	}
	return (_cmp_result(s1, s2));
}

static int	_cmp_result(const char *s1, const char *s2)
{
	unsigned char	*str1_ptr;
	unsigned char	*str2_ptr;

	str1_ptr = (unsigned char *)s1;
	str2_ptr = (unsigned char *)s2;
	return (*str1_ptr - *str2_ptr);
}

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
