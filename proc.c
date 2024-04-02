
#include <stdio.h>
//TODO eliminar
int main (int argc, char *argv[])
{
	int i = 0;

	printf("holadola\n");
	if (argc > 1)
		while (argv[i])
			printf("%s\n", argv[i++]);
	return (0);
}
