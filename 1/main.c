#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE*	file = NULL;
	ssize_t	read;
	size_t	n = 0;
	char*	lineptr = NULL;
	int		out = 0;
	unsigned int score = 0;

	if(argc != 2)
	{
		printf("%s FILE\n", argv[0]);
		return -1;
	}

	if((file = fopen(argv[1], "r")) == NULL)
		goto err;

	if((read = getline(&lineptr, &n, file)) < 0)
		goto err;

	for(char* str = lineptr; *str != '\0'; str++)
	{
		char next = *(str + 1);

		/* The list is circular, so the first character in the string is
		 * reconsidered.
		 */
		if(next == '\0')
			next = *lineptr;

		//printf("Comparing %c and %c.", *str, next);

		if(*str == next)
		{
			score += (*str - '0'); /* Convert char to int */
		//	printf(" Added %d", (*str - '0'));
		}
		
		//printf("\n");
	}

	printf("Answer: %d\n", score);

out:
	free(lineptr);

	if(file != NULL)
		fclose(file);
	
	return out;

err:
	printf("%s\n", strerror(errno));
	out = errno;
	goto out;
}
