#include "shell.h"

/**
 * command_path - Finds the full path of a command in PATH.
 * @command: The command to locate.
 * @env: The environment variables array.
 * Return: Dynamically allocated string with the full path of the command,
 *         or NULL if the command is not found or an error occurs.
 */
char *command_path(char *command, char **env)
{
	char *path, *path_copy, *dir, *full_path;

	struct stat st;
	/* If the command contains '/', check if it exists as-is */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == -1)
		{
			perror("Error checking file");
			return (NULL);
		}
		if (stat(command, &st) == 0 && S_ISREG(st.st_mode) && access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	/* Pass env to custom_getenv */
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
