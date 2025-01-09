#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;

	(void)argc, (void)argv;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		read_size = getline(&input, &input_size, stdin);
		if (read_size == -1) /* Handle Ctrl+D or EOF */
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0';

		if (!process_input(input, env))
			execute_command(input, env);
	}
	free(input);
	return (0);
}
