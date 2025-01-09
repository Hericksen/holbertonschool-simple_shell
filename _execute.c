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
    if (!args || !args[0])
    {
        free_args(args);
        return;
    }

    /*Pass env to get_command_path*/
    path = get_command_path(args[0], env);
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
        /* Pass env to execve*/
        if (execve(path, args, env) == -1)
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
/**
 * free_args - Frees the argument array
 * @args: The argument array to free
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
