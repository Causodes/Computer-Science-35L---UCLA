#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char** argv)
{
	int i, j, k;
	if (argc != 3)
	{
		fprintf(stderr, "Error, please provide exactly 2 arguments");
		exit(1);
	}

	char* from = argv[1];
	char* to = argv[2];

	if (strlen(from) != strlen(to))
	{
		fprintf(stderr, "Error, argument lengths do not match");
		exit(1);
	}

	for (i = 0; i < strlen(from); i++)
	{
		for (j = i + 1; j < strlen(from); j++)
		{
			if (from[j] == from[i])
			{
				fprintf(stderr, "Error, duplicate bytes in argument");
				exit(1);
			}
		}
	}

	char c;
	ssize_t status = read(STDIN_FILENO, &c, 1);
	while (status > 0)
	{
		for (k = 0; k < strlen(from); k++)
		{
			if (c == from[k])
			{
				c = to[k];
				break;
			}
		}
		write(STDOUT_FILENO, &c, 1);
		status = read(STDIN_FILENO, &c, 1);
	}
	return 0;
}