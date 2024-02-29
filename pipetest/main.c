

#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define WRITE_END	1
#define READ_END	0

int main(void)
{
	int pipefd[2];
	size_t pid;
	char buffer[100];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		write(pipefd[WRITE_END], "ola que ase", 12);
		printf("cmd1 redir - ola que ase\n");
		printf("cmd1 out - ola que ase\n");
	}
	else
	{
		read(pipefd[READ_END], buffer, sizeof(buffer));
		printf("shell buff - %s\n", buffer);
		pid = fork();
		if (pid == 0)
		{
			read(pipefd[READ_END], buffer, sizeof(buffer));
			printf("cmd2 redir - %s\n", buffer);
			printf("cmd2 input - %s\n", buffer);
		}
		else
		{
			memcpy(&buffer[11]," ola que frio\0", 15);
			write(pipefd[WRITE_END], buffer, sizeof(buffer));
		}
	}
	return (0);
}
