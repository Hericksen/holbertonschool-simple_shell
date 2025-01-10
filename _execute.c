#include "shell.h"
/**
 * tokenizazion - Tokenizes a string into an array of words.
 * @input: The input string to tokenize. This string is modified in-place.
 *
 * Return: A dynamically allocated array of tokens, ending with NULL.
 *         Returns NULL on memory allocation failure.
 */
char **tokenizazion(char *input)
{
	char **tokens = NULL;
	char *token;
	size_t token_count = 0;
	size_t input_length;
	size_t max_possible_tokens;

	if (input == NULL)
		return (NULL);

	input_length = strlen(input);

	/* Estimate the maximum number of tokens:*/
	max_possible_tokens = input_length / 2 + 1;

	/* Allocate memory for the array of tokens */
	tokens = (char **)malloc((max_possible_tokens + 1) * sizeof(char *));
	if (tokens == NULL) /* Check for allocation failure */
		return (NULL);

	/* Tokenize the input string using strtok */
	token = strtok(input, " \t\n"); /* Split on spaces, tabs, or newlines */
	while (token != NULL)
	{
		tokens[token_count] = token; /* Store the token in the array */
		token_count++;
		token = strtok(NULL, " \t\n"); /* Get the next token */
	}

	/* Null-terminate the array of tokens */
	tokens[token_count] = NULL;

	return (tokens); /* Return the array of tokens */
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
		exit(EXIT_FAILURE);
	}
	path = command_path(args[0], env);
	if (path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free(args);
		free(path);
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(args);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			perror("execve");
			free(args);
			free(path);
			exit(EXIT_FAILURE); /* Use EXIT_FAILURE only if available */
		}
	}
	else
		wait(&status);
	free(args);
	free(path);
}
