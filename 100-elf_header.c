#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/types.h>

#define BUFFER_SIZE 64

/**
 * print_error_and_exit - Prints error message and exits with the specified code.
 * @exit_code: Exit code to use.
 * @message: Error message to print.
 */
void print_error_and_exit(int exit_code, const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
	exit(exit_code);
}

/**
 * print_elf_header_info - Prints the information contained in the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_elf_header_info(Elf64_Ehdr *header)
{
	int i;

	printf("Magic: ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", header->e_ident[i]);
	printf("\n");

	printf("Class: %u\n", header->e_ident[EI_CLASS]);
	printf("Data: %u\n", header->e_ident[EI_DATA]);
	printf("Version: %u\n", header->e_ident[EI_VERSION]);
	printf("OS/ABI: %u\n", header->e_ident[EI_OSABI]);
	printf("ABI Version: %u\n", header->e_ident[EI_ABIVERSION]);

	printf("Type: %u\n", header->e_type);
	printf("Entry point address: %lx\n", (unsigned long)header->e_entry);
}

/**
 * read_elf_header - Reads the ELF header from the specified file.
 * @filename: Name of the ELF file.
 */
void read_elf_header(const char *filename)
{
	int fd;
	ssize_t bytes_read;
	Elf64_Ehdr header;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error_and_exit(98, "Error: Cannot open file");

	bytes_read = read(fd, &header, sizeof(header));
	if (bytes_read == -1)
		print_error_and_exit(98, "Error: Cannot read from file");

	if (bytes_read != sizeof(header))
		print_error_and_exit(98, "Error: Incomplete read");

	print_elf_header_info(&header);

	close(fd);
}

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success, 98 on error.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
		print_error_and_exit(98, "Usage: elf_header elf_filename");

	read_elf_header(argv[1]);

	return (0);
}

