

#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
	int i = 0;

	while (str && str[i])
		i++;
	return (i);
}

char *cut_line(char *resto)
{
	int i = 0, j = 0;

	while (resto[i] && resto[i] != '\n')
		i++;
	if (!resto[i])
	{
		free(resto);
		return (NULL);
	}
	char *res = malloc(ft_strlen(resto) - i + 1);
	i++;
	while (resto[i])
		res[j++] = resto[i++];
	res[j] = '\0';
	free(resto);
	return (res);
}

char *push_line(char *resto)
{
	int i = 0;

	while (resto[i] && resto[i] != '\n')
		i++;
	if (resto[i] == '\n')
		i++;
	char *res = malloc(i + 1);
	i = 0;
	while (resto[i] && resto[i] != '\n')
	{
		res[i] = resto[i];
		i++;
	}
	if (resto[i] == '\n')
	{
		res[i] = '\n';
		res[i + 1] = '\0';
		return (res);
	}
	else
		res[i] = '\0';
	return (res);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0, j = 0;
	char *res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);

	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
		free(s1);
	}
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

int is_line(char *buffer)
{
	int i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1] = {0};
	static char *resto = NULL;
	char *line = NULL;
	int rd = 1;

	while (!is_line(buffer) && rd != 0)
	{
		if ((rd = read(fd, buffer, BUFFER_SIZE)) < 0)
		{
			if (resto)
			{
				free(resto);
				resto = NULL;
			}
			return (NULL);
		}
		buffer[rd] = '\0';
		resto = ft_strjoin(resto, buffer);
	}

	line = push_line(resto);
	resto = cut_line(resto);

	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int	fd = open(argv[1], O_RDONLY);
	char *line = get_next_line(fd);

	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}
