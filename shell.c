#include "shell.h"
/**
 * main - Entry point for the simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read_size = getline(&input, &input_size, stdin);
		if (read_size == -1)
			break;

		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0';

		if (strcmp("exit", input) == 0)
		{
			free(input);
			exit(0);
		}

		execute_command(input);
	}

	free(input);
	return (0);
}
