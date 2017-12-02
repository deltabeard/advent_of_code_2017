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
		int high;
		int low;
		char* token = strtok(lineptr, "\t");

		if(token == NULL)
			continue;

		high = low = atoi(token);

		while((token = strtok(NULL, "\t")) != NULL)
		{
			int num = atoi(token);

			if(num > high)
				high = num;
			else if(num < low)
				low = num;
		}

		answer += abs(high - low);
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
