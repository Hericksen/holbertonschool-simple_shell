#include "shell.h"
/**
 * tokenizazion - Splits the input into tokens
 * @input: The input string
 *
 * Return: Array of strings (tokens)
 */
char **tokenizazion(char *input)
{
	char **tokens = NULL;
	char *token;
	int token_count = 0;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	if (!tokens)
		return (NULL);

	token = strtok(input, " \t\n");
	while (token && token_count < MAX_TOKENS - 1)
	{
		tokens[token_count] = token;
		token_count++;
		token = strtok(NULL, " \t\n");
	}
	tokens[token_count] = NULL;

	return (tokens);
}
/**
 * execute_command - Executes the given command.
 * @command: The command to execute.
 * @env: The environment variables array.
 */
void execute_command(char *command, char **env)
{
	char **args;
	char *path;
	pid_t child_pid;
	int status;

	args = tokenizazion(command);
	if (args == NULL || args[0] == NULL)
	{
		free(args);
		return;
	}

	path = get_command_path(args[0], env);
	if (path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free(args);
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	else if (child_pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			perror("execve");
			exit(1); /* Use EXIT_FAILURE only if available */
		}
	}
	else
	{
		wait(&status);
	}
	free(args);
	free(path);
}
