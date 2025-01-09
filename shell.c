#include "shell.h"
/**
 * main - The main shell loop.
 * @argc: The argument count.
 * @argv: The argument vector.
 * @env: The environment variables.
 *
 * Return: 0 on success, exits with status 0 on 'exit' command.
 */
int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;

	(void)argc, (void)argv; /* Unused parameter */
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		read_size = getline(&input, &input_size, stdin);
		/* If Ctrl+D is pressed, read_size will be -1 and we'll break the loop */
		if (read_size == -1)
		{
			write(STDOUT_FILENO, "\n", 1); /* Add a newline before exiting */
			break;
		}
		/* Remove newline character if present */
		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0';

		if (strcmp("exit", input) == 0)
		{
			free(input);
			exit(0);
		}

		else if (strcmp("env", input) == 0)
		{
			print_env(env);
			continue;
		}
		else if (strncmp("which", input, 5) == 0)
		{
			handle_which_command(input, env);
			continue;
		}
		execute_command(input, env);
	}
	free(input);
	return (0);
}
