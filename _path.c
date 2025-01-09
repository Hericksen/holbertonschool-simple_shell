#include "shell.h"


/**
* custom_getenv - Retrieves the value of an environment variable.
* @name: The name of the environment variable to find.
*
* Return: Pointer to the value of the environment variable,
*         or NULL if the variable is not found.
*/
char *custom_getenv(const char *name)
{
	size_t name_len;
	char **env;

	if (!name || !*name)
		return (NULL);

	name_len = strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		/* Check if the current variable starts with the name and is followed by '=' */
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			/* Return the value part (after the '=') */
			return (&((*env)[name_len + 1]));
		}
	}

	return (NULL);
}

/**
* get_command_path - Finds the full path of a command in PATH.
* @command: The command to locate.
*
* Return: Dynamically allocated string with the full path of the command,
*         or NULL if the command is not found or an error occurs.
*/
char *get_command_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;

	struct stat st;

	/* If the command contains '/', check if it exists as-is */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = custom_getenv("PATH");
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
		if (stat(full_path, &st) == 0)
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
