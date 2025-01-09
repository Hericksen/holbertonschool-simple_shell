#include "shell.h"
/**
 * main - Entry point for the simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Environment variables array
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
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

		/*Handle exit command */
		if (strcmp("exit", input) == 0)
		{
			free(input); /*Free allocated memory*/
			exit(0);	 /*Exit the shell successfully*/
		}
		else if (strcmp("env", input) == 0)
		{
			print_env(env);
			continue;
		}

		/*Execute other commands*/
		execute_command(input, env);
	}

	free(input);
	return (0);
}
