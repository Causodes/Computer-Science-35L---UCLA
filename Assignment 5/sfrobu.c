#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "unistd.h"
#include <sys/stat.h>
#include "limits.h"

char decode(char c) 
{
	return c ^ 42;
}

int frobcmp(char const * a, char const * b) 
{
	for (; ; a++, b++) {
		if (*a == ' ' && *b == ' ')
			return 0;
		if (*a == ' ' || decode(*a) < decode(*b))
			return -1;
		if (*b == ' ' || decode(*a) > decode(*b))
			return 1;
	}

}
void check(ssize_t status) 
{
	if (status < 0) 
	{
		fprintf(stderr, "Error, can't read from stdin");
		exit(1);
	}
}

int compare(const void * c1, const void * c2) 
{
	return frobcmp(*(const char **)c1, *(const char **)c2);
}

typedef char * string;

int main(int argc, char *argv[])
{
	if (argc == 2 && strcmp(argv[1], "-f") != 0)
	{
		fprintf(stderr, "Error, only -f permitted");
		exit(1);
	}
	else if (argc > 2)
	{
		fprintf(stderr, "Error, too many options");
		exit(1);
	}

	string x;
	string * y;
	int i = 0;
	int j = 0;
	int numWords = 0;
	int numChars = 0;
	x = (string)malloc(sizeof(char));
	y = (string *)malloc(sizeof(string));

	if (x == NULL || y == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.");
		exit(1);
	}
	char c;
	ssize_t status = read(STDIN_FILENO, &c, 1);

	check(status);
	char end = c;

	while (status > 0) 
	{
		if (feof(stdin) || ferror(stdin)) 
		{
			break;
		}

		if (c == ' ' && numChars >= 1) 
		{
			x[numChars] = '\0';
			y[numWords] = x;
			string * tmp = realloc(y, (numWords + 2) * sizeof(string));
			if (tmp != NULL) 
			{
				y = tmp;
				numWords++;
				x = (char*)malloc(sizeof(char));
				numChars = 0;
			}
			else 
			{
				free(x);
				fprintf(stderr, "Error: Memory allocation failed.");
				exit(1);
			}
		}

		else 
		{
			x[numChars] = c;
			string tmp = realloc(x, (numChars + 2) * sizeof(char));
			if (tmp != NULL) 
			{
				x = tmp;
				numChars++;
			}
			else 
			{
				free(y);
				fprintf(stderr, "Error: Memory allocation failed.");
				exit(1);
			}

		}
		end = c;
		status = read(STDIN_FILENO, &c, 1);
		check(status);
		if (status <= 0) 
		{
			if (end == ' ') 
			{
				break;
			}
			else if (numChars >= 1) 
			{
				y[numWords] = x;
				string * tmp = realloc(y, (numWords + 2) * sizeof(string));
				if (tmp != NULL)
				{
					y = tmp;
					numWords++;
					x = (char*)malloc(sizeof(char));
					numChars = 0;
				}
				else 
				{
					free(y);
					fprintf(stderr, "Error: Memory allocation failed.");
					exit(1);
				}
				break;
			}
		}

		else if (c == ' '  && end == ' ')
		{
			while (c == ' ') 
			{
				status = read(STDIN_FILENO, &c, 1);
				check(status);
			}
			numChars = 0;
		}
	}
	qsort(y, numWords, sizeof(string), compare);

	for (i = 0; i < numWords; i++) 
	{
		for (j = 0; ; j++) 
		{
			if (y[i][j] == '\0')
			{
				break;
			}
			else if (y[i][j] == ' ') 
			{
				status = write(STDOUT_FILENO, &y[i][j], 1);
				check(status);
				break;
			}
			else 
			{
				status = write(STDOUT_FILENO, &y[i][j], 1);
			}
		}
		char tmp = ' ';
		status = write(STDOUT_FILENO, &tmp, 1);
	}

	for (i = 0; i< numWords; i++)
	{
		free(y[i]);
	}
	free(y);
	exit(0);
}
