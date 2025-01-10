#include "shell.h"

int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;

	(void)argc;
	(void)argv;

	while (1)
	{
		/* Show the prompt in interactive */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read input */
		read_size = getline(&input, &input_size, stdin);
		if (read_size == -1) /* Eof or error */
		{
			if (isatty(STDIN_FILENO)) /* If interactive, display a message */
				write(STDOUT_FILENO, "\nExiting shell...\n", 18);
			free(input);
			_exit(EXIT_SUCCESS);
		}

		/* Delete the \n */
		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0';

		/* Command "exit" */
		if (strcmp("exit", input) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		/* Command "env" */
		if (strcmp("env", input) == 0)
		{
			print_env(env);
			continue; /* Come back to the start of the loop */
		}

		/* Command "which" */
		if (strncmp("which", input, 5) == 0)
		{
			char *command = input + 6; /* Skip "which " (5 char + space) */
			char *path = custom_which(command, env);
			if (path)
			{
				printf("%s\n", path);
				free(path);
			}
			else
			{
				fprintf(stderr, "Command not found: %s\n", command);
			}
			continue; /* Come to the begin of the loop */
		}

		/* Exec other commands */
		execute_command(input, env);
	}

	free(input);
	_exit(0);
}
