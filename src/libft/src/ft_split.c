/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:26:44 by fmontser          #+#    #+#             */
/*   Updated: 2023/07/18 17:49:36 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define END 1

static int	_count_items(const char *s, char c)
{
	int		count;
	bool	i_flag;

	count = 0;
	i_flag = false;
	while (*s != '\0')
	{
		while (*s != c && *s != '\0')
		{
			if (!i_flag)
			{
				i_flag = true;
				count++;
			}
			s++;
		}
		if (*s == '\0')
		{
			return (count);
		}
		i_flag = false;
		s++;
	}
	return (count);
}

static int	_count_chars(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s != c && *s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	int		i;
	int		j;

	split = ft_calloc(_count_items(s, c) + END, sizeof(char *));
	if (!split)
		return (NULL);
	j = 0;
	while (*s != '\0')
	{
		i = _count_chars(s, c);
		s += i;
		if (i > 0)
		{
			split[j] = ft_calloc(i + NUL_SZ, sizeof(char));
			if (!split[j])
				return (NULL);
			ft_strlcpy(split[j++], s - i, i + NUL_SZ);
			continue ;
		}
		s++;
	}
	return (split);
}
