#include "shell.h"

/**
 * tokenizazion - Splits the input into tokens
 * @input: The input string
 *
 * Return: Array of strings (tokens)
 */
char **tokenizazion(char *input)
{
	char **tokens;
	int token_count;
	char *start, *end, *delimiters;

	/* Check for null input string */
	if (!input)
		return (NULL);

	/* Allocate memory for tokens array */
	tokens = malloc(sizeof(char *) * (MAX_TOKENS + 1));
	if (!tokens)
		return (NULL);

	token_count = 0;
	delimiters = " \t\n"; /* Delimiters for tokenizing input string */
	start = input;

	/* Tokenize input string */
	while (token_count < MAX_TOKENS && *start)
	{
		/* Skip leading delimiters */
		while (*start && strchr(delimiters, *start))
			start++;

		/* If end of string is reached, stop tokenizing */
		if (!*start)
			break;

		end = start;
		/* Find the end of the current token */
		while (*end && !strchr(delimiters, *end))
			end++;
		; /* Null-terminate the token */
		*end = '\0';
		tokens[token_count++] = start; /* Store token */
		start = end + 1;			   /* Move to the next potential token */
	}
	/* Null-terminate the tokens array */
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

	/* Tokenize the command string */
	args = tokenizazion(command);
	if (!args || !args[0])
	{
		free(args);
		return;
	}

	/* Get command path from environment */
	path = get_command_path(args[0], env);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		fflush(stderr); /* Flush stderr buffer */
		free(args);
		return;
	}

	/* Execute the command by forking */
	fork_and_execute(args, path, env);

	/* Clean up memory */
	free(args);
	free(path);
}
/**
 * fork_and_execute - Forks a child process to execute the command.
 * @args: The arguments of the command.
 * @path: The path to the command executable.
 * @env: The environment variables array.
 */
void fork_and_execute(char **args, char *path, char **env)
{
	pid_t child_pid;
	int status;

	/* Create a child process */
	child_pid = fork();
	if (child_pid == -1)
	{
		/* Handle fork error */
		perror("fork");
		fflush(stderr); /* Flush stderr buffer */
		free(args);
		free(path);
		return;
	}

	if (child_pid == 0)
	{
		/* In the child process, try to execute the command */
		if (execve(path, args, env) == -1)
		{
			/* If execve fails, print the error */
			perror("execve");
			fflush(stderr); /* Flush stderr buffer */
			free(args);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
/**
 * free_args - Frees the argument array
 * @args: The argument array to free
 */
