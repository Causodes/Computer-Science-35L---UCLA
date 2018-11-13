#include <stdio.h>
#include <stdlib.h>

int decode(char c)
{
	return c ^ 42;
}

int frobcmp(char const *a, char const *b)
{
	for (;; a++, b++)
	{
		if (*a == ' ' && *b == ' ')
			return 0;
		else if (*b == ' ' || decode(*a) > decode(*b))
			return 1;
		else if (*a == ' ' || decode(*a) < decode(*b))
			return -1;
	}
}

void invalidIO()
{
	if (ferror(stdin))
	{
		fprintf(stderr, "Error");
		exit(1);
	}
}

int cmp(const void *a, const void *b) {
	return frobcmp(*(const char **)a, *(const char **)b);
}

int main()
{
	char *x;
	char **y;
	int i = 0;
	int j = 0;
	int numChars = 0;
	int numWords = 0;
	x = (char *)malloc(sizeof(char));
	y = (char **)malloc(sizeof(char *));

	if (x == NULL || y == NULL) 
	{
		fprintf(stderr, "Memory Allocation Error");
		exit(1);
	}

	while (!feof(stdin))
	{
		char c = getchar();
		invalidIO();
		x = (char*)realloc(x, (numChars + 1) * sizeof(char));
		if (numChars > 0 && (c == ' ' || feof(stdin) || c == EOF))
		{	
			x[numChars] = ' ';
			y = (char**)realloc(y, (numWords + 1) * sizeof(char *));
			char *z = (char*)malloc(sizeof(char*));

			if (z != NULL && y != NULL)
			{
				y[numWords] = x;
				x = z;
				numChars = 0;
				numWords++;
			}

			else
			{
				fprintf(stderr, "Memory Allocation Error");
				free(x);
				exit(1);
			}
		}

		else if (x != NULL)
		{
			x[numChars] = c;
			numChars++;
		}

		else
		{
			fprintf(stderr, "Memory Allocation Error");
			exit(1);
		}
	}

	qsort(y, numWords, sizeof(char *), cmp);

	for (i = 0; i < numWords; i++)
	{
		for (j = 0;; j++)
		{
			if (y[i][j] == '\0')
				break;

			putchar(y[i][j]);

			if (y[i][j] == ' ')
				break;
		}
	}

	for (i = 0; i < numWords; i++)
		free(y[i]);
	free(y[i]);
	exit(0);
}