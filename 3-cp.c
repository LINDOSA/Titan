#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

/**
 * print_error_and_exit - Prints error message and exits with specified code.
 * @exit_code: Exit code to use.
 * @message: Error message to print.
 */
void print_error_and_exit(int exit_code, const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(exit_code);
}

/**
 * cp_file - Copies content from source file to destination file.
 * @file_from: Source file name.
 * @file_to: Destination file name.
 */
void cp_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to;
	ssize_t bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];

	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
		print_error_and_exit(98, "Error: Can't read from file");

	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_to == -1)
		print_error_and_exit(99, "Error: Can't write to file");

	while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);
		if (bytes_written == -1)
			print_error_and_exit(99, "Error: Can't write to file");
	}

	if (bytes_read == -1)
		print_error_and_exit(98, "Error: Can't read from file");

	close(fd_from);
	close(fd_to);
}

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success, 97 on incorrect number of arguments.
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
		print_error_and_exit(97, "Usage: cp file_from file_to");

	cp_file(argv[1], argv[2]);

	return (0);
}

