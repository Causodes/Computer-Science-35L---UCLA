#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void checkIO()
{
	if (ferror(stdin))
	{
		fprintf(stderr, "Error reading from stdin");
		exit(1);
	}
}

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

	int c = getchar();
	checkIO();

	while (c != EOF)
	{
		for (k = 0; k < strlen(from); k++)
		{
			if (c == from[k])
			{
				c = to[k];
				break;
			}
		}
		putchar(c);
		c = getchar();
		checkIO();
	}

	return 0;
}
