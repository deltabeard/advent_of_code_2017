#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE*	file = NULL;
	ssize_t	read;
	size_t	n = 0;
	char*	lineptr = NULL;
	int		out = 0;
	unsigned int answer = 0;

	if(argc != 2)
	{
		printf("%s FILE\n", argv[0]);
		return -1;
	}

	if((file = fopen(argv[1], "r")) == NULL)
		goto err;

	while(getline(&lineptr, &n, file) != -1)
	{
		char*	token = strtok(lineptr, "\t");
		int*	array = NULL;
		size_t	nmemb = 0;
		unsigned int result;

		while(token != NULL)
		{
			/* Reallocate array for new integer */
			array = realloc(array, ++nmemb * sizeof(int));

			if(array == NULL)
				goto err;

			/* Convert the string to an integer, then store the integer in the
			 * array.
			 */
			*(array + (nmemb - 1)) = atoi(token);

			token = strtok(NULL, "\t");
		}

		result = 0;

		for(int i = 0; i < nmemb; i++)
		{
			printf("%d\t", *(array + i));

			for(int j = 0; j < nmemb; j++)
			{
				if(i == j)
					continue;

				if(*(array + i) % *(array + j) == 0)
				{
					int temp = *(array + i) / *(array + j);

					if(temp > result)
						result = temp;
				}
			}
		}

		printf("-> %d\n", result);
		printf("\n");
		answer += result;

		free(array);
	}

	printf("Answer: %d\n", answer);

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
