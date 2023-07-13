#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

/**
 * create_file - Create a file and write content to it.
 * @filename: Name of the file to create.
 * @text_content: Content to write to the file.
 *
 * Return: 1 on success, -1 on failure.
 */
int create_file(const char *filename, char *text_content)
{
	if (filename == NULL)
		return (-1);

	int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	if (file == -1)
		return (-1);

	if (text_content != NULL)
	{
		ssize_t bytesWritten = write(file, text_content, strlen(text_content));

		if (bytesWritten == -1)
		{
			close(file);
			return (-1);
		}
	}

	close(file);
	return (1);
}

