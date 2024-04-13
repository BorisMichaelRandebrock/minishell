/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:43:36 by fmontser          #+#    #+#             */
/*   Updated: 2024/04/13 10:48:49 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>
#define NUL_SZ	1
#define BUFFER_SIZE 1

static char	*_get_line(char *buffer, char *line_end)
{
	size_t	line_size = (line_end - buffer) + NUL_SZ;
	char *	line = malloc(line_size * sizeof(char));
	size_t	i = 0;

	if(!line)
		return (NULL);
	while(i < line_size)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return(line);
}

static void _fwd_stack(char *stack, char *new_line)
{
	size_t size =  _strlen(new_line);
	size_t i = 0;

	while(i < size)
	{
		stack[i] = new_line[i];
		i++;
	}
	stack[i] = '\0';
}



static void _stack_buffer(char *stack, char *buffer)
{
	size_t stack_sz = _strlen(stack);
	size_t buffer_sz = _strlen(buffer);
	size_t i = 0;

	while (i < buffer_sz)
	{
		stack[stack_sz + i] = buffer[i];
		i++;
	}
	stack[stack_sz + i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	stack[INT32_MAX] = {0};
	char		buffer[BUFFER_SIZE + NUL_SZ] = {0};
	int		i = 0;
	ssize_t		readen = 1;
	char		*line;

	if (fd < 0)
		return (NULL);
	while(readen)
	{
		readen = read(fd, buffer, BUFFER_SIZE);
		if (readen < 0)
			return (NULL);
		if (readen == 0)
			break;
		buffer[readen] = '\0';
		_stack_buffer(stack, buffer);
		while (i < _strlen(stack))
		{
			if (stack[i] == '\n')
			{
				line = _get_line(stack, &stack[i]);
				_fwd_stack(stack, &stack[i + 1]);
				return (line);
			}
			i++;
		}
		i = 0;
	}
	if (readen == 0 && *stack)
	{
		line =  _get_line(stack, &stack[_strlen(stack)]);
		stack[0] = '\0';
		return (line);
	}
	return (NULL);
}
