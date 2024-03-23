/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:33:04 by fmontser          #+#    #+#             */
/*   Updated: 2024/03/23 12:45:26 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	fm_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s && s[length++])
		;
	return (length);
}
