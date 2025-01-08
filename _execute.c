#include "shell.h"

/**
 * execute_command - Executes the given command
 * @command: The command to execute
 */
void execute_command(char *command)
{
	char **args;
	char *path;
	pid_t child_pid;
	int status;

	args = tokenize_input(command);
	if (!args || !args[0])
	{
		free_args(args);
		return;
	}

	path = get_command_path(args[0]);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free_args(args);
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free_args(args);
		free(path);
		return;
	}

	if (child_pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	free_args(args);
	free(path);
}
