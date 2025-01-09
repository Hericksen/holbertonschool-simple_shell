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
/**
 * process_input - Handles input processing for commands.
 * @input: Input string to process
 * @env: Environment variables
 * Return: 1 if successful, 0 if EOF is reached.
 */
int process_input(char *input, char **env)
{
	char *command, *path;

	if (strcmp("exit", input) == 0)
	{
		free(input);
		exit(0);
	}
	if (strcmp("env", input) == 0)
	{
		print_env(env);
		return (1);
	}
	if (strncmp("which", input, 5) == 0)
	{
		command = input + 6; /* Skip "which " */
		path = custom_which(command, env);
		if (path)
		{
			printf("%s\n", path);
			free(path);
		}
		else
			fprintf(stderr, "Command not found: %s\n", command);
		return (1);
	}
	return (0);#include "shell.h"
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
}
