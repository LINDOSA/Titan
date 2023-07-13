#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * read_textfile - Read text file and print to STDOUT.
 * @filename: Name of the text file.
 * @letters: Number of letters to be read.
 *
 * Return: The actual number of bytes read and printed.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	FILE *file;
	char *buffer;
	ssize_t bytesRead;

	if (filename == NULL)
		return (0);

	file = fopen(filename, "r");
	if (file == NULL)
		return (0);

	buffer = malloc(sizeof(char) * (letters + 1));
	if (buffer == NULL)
	{
		fclose(file);
		return (0);
	}

	bytesRead = fread(buffer, sizeof(char), letters, file);
	buffer[bytesRead] = '\0';

	printf("%s", buffer);

	free(buffer);
	fclose(file);

	return bytesRead;
}

