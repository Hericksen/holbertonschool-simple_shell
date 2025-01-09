#include "shell.h"
/**
 * custom_getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable to get.
 * @env: The environment variables array.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *custom_getenv(const char *name, char **env)
{
	int i;
	char *env_var;
	size_t name_len = strlen(name);

	for (i = 0; env[i] != NULL; i++)
	{
		env_var = env[i];

		/*Compare the beginning of the string with the environment variable name*/
		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
			return (env_var + name_len + 1);
		/* Return the value part of the environment variable*/
	}
	return (NULL);
}
/**
 * get_command_path - Retrieves the full path of a command from PATH.
 * @command: The command to search for.
 * @env: The environment variables array.
 *
 * Return: Full path to the command or NULL if not found.
 */
char *get_command_path(char *command, char **env)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;
	size_t full_path_len;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0 && S_ISREG(st.st_mode) && access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = custom_getenv("PATH", env);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path_len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(full_path_len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		/* Construct the full path */
		full_path[0] = '\0';
		strcat(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		/* Check if the command is executable */
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * print_env - Prints the current environment variables.
 * @env: The environment variables array.
 */
void print_env(char **env)
{
	if (!env || !*env)
	{
		fprintf(stderr, "Error: Environment is empty or invalid.\n");
		return;
	}

	for (; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
/**
 * custom_which - Finds the full path of a command in PATH.
 * @command: The command to locate.
 * @env: The environment variables array.
 *
 * Return: The full path of the command if found, or NULL if not.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 1024

/**
 * custom_which - Searches for the command in the directories listed in PATH.
 * @cmd: The command to search for.
 * @env: The environment variables array.
 *
 * Return: Full path to the command if found, NULL otherwise.
 */
char *custom_which(const char *cmd, char **env)
{
	char full_path[MAX_PATH_LENGTH];
	char *path_env = custom_getenv("PATH", env); /* Retrieve the PATH environment variable */
	char *path_copy = strdup(path_env);
	char *dir = strtok(path_copy, ":");
	/* If the command starts with '/' or './', it's already an absolute or relative path */
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		/* Check if the file exists and is executable */
		if (access(cmd, X_OK) == 0)
		{
			return strdup(cmd); /* Return the absolute/relative path if executable */
		}
		return NULL; /* If not executable, return NULL */
	}

	/* Otherwise, search the directories in PATH */
	if (path_env == NULL)
	{
		return NULL; /* If PATH is not set, return NULL */
	}

	/* Duplicate the PATH string for tokenization */
	if (path_copy == NULL)
	{
		perror("strdup");
		return NULL;
	}

	/* Tokenize the PATH based on the colon (':') separator */
	while (dir != NULL)
	{
		/* Construct the full path to the executable */
		full_path[0] = '\0'; /* Initialize the string to empty */

		/* Concatenate the directory and command */
		strcat(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		/* Check if the file exists and is executable */
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);		  /* Free the duplicated PATH string */
			return strdup(full_path); /* Return the full path of the executable */
		}

		/* Move to the next directory in PATH */
		dir = strtok(NULL, ":");
	}

	free(path_copy); /* Free the duplicated PATH string */
	return NULL;	 /* If the command was not found in any directory, return NULL */
}

/**
 * handle_which_command - Handles the 'which' command in the shell.
 * @input: The user input containing the command.
 * @env: The environment variables.
 */
void handle_which_command(char *input, char **env)
{
	char **args = tokenizazion(input);
	char *path = custom_which(args[1], env);
	if (!args || !args[1])
	{
		fprintf(stderr, "Usage: which <command>\n");
		free(args);
		return;
	}

	/* Search for the executable using which */
	if (path)
	{
		printf("%s found at: %s\n", args[1], path);
		free(path);
	}
	else
	{
		printf("%s not found in PATH.\n", args[1]);
	}

	free(args);
}
