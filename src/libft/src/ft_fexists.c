/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fexists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:31:37 by fmontser          #+#    #+#             */
/*   Updated: 2023/11/18 23:02:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_MISSING -1

bool	ft_fexists(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == FILE_MISSING)
	{
		close(fd);
		return (false);
	}
	else
	{
		close(fd);
		return (true);
	}
}
