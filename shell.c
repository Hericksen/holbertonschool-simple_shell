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
		else if (strcmp("env", input) == 0)
		{
			print_env(env);
			continue;
		}
		else if (strncmp("which", input, 5) == 0)
		{
			char *command = input + 6;/*Skip "which " (5 characters + 1 space)*/
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
			continue;
		}

		execute_command(input, env);
	}

	free(input);
	return 0;
}
