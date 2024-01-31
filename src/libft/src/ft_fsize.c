/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fsize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:22:56 by fmontser          #+#    #+#             */
/*   Updated: 2023/10/09 21:23:52 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

int	ft_fsize(char *file_path)
{
	char	dispose;
	int		byte_count;
	int		fd;

	byte_count = 0;
	fd = open(file_path, O_RDONLY);
	while (read(fd, &dispose, sizeof(char)) != READ_EOF)
		byte_count++;
	close(fd);
	return (byte_count);
}
