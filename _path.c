#include "shell.h"
/**
 * custom_getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable to get.
 * @env: The environment variables array.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *custom_getenv(char *name, char **env)
{
	size_t name_len;
	char *current;

	if (!name || !*name)
		return (NULL);

	name_len = strlen(name);

	/* Loop through each environment variable */
	while (*env != NULL)
	{
		current = *env;

	/*Check if the current variable starts with the name and is followed by '='*/
		if (strncmp(current, name, name_len) == 0 && current[name_len] == '=')
		{
			/* Return the value part (after the '=') */
			return (current + name_len + 1);
		}

		env++;
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
		if (stat(command, &st) == 0 && S_ISREG(st.st_mode)
		&& access(command, X_OK) == 0)
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
 * which - Finds the full path of a command in PATH.
 * @command: The command to locate.
 * @env: The environment variables array.
 *
 * Return: The full path of the command if found, or NULL if not.
 */
char *custom_which(char *command, char **env)
{
	char *path, *path_copy, *dir, *full_path;

	struct stat st;

	if (strchr(command, '/') != NULL)
	{
		/* If the command contains '/', check if it exists as-is */
		if (stat(command, &st) == 0 && S_ISREG(st.st_mode) && access(command, X_OK) == 0)
			return strdup(command);
		return (NULL);
	}

	/* Retrieve PATH from the environment */
	path = custom_getenv("PATH", env);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) &&
			access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path); /* Return the full path if the command is found */
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Return NULL if the command was not found in PATH */
}
/**
 * handle_which_command - Handles the 'which' command in the shell.
 * @input: The user input containing the command.
 * @env: The environment variables.
 */
void handle_which_command(char *input, char **env)
{
	char *command = input + 6; /* Skip "which " (5 characters + 1 space) */
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
}
