#include "shell.h"

/**
* custom_getenv - Retrieves the value of an environment variable.
* @name: The name of the environment variable to find.
* @env: The environment variables array.
*
* Return: Pointer to the value of the environment variable,
*         or NULL if the variable is not found.
*/
char *custom_getenv(const char *name, char **env)
{
	size_t name_len;

	if (!name || !*name)
		return (NULL);

	name_len = strlen(name);

	for (; *env != NULL; env++)
	{
	/*Check if the current variable starts with the name and is followed by '='*/
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			/* Return the value part (after the '=') */
			return (&((*env)[name_len + 1]));
		}
	}

	return (NULL);
}
/**
* custom_which - Finds the full path of a command in PATH.
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
		if (stat(command, &st) == 0 && S_ISREG(st.st_mode)
		&& access(command, X_OK) == 0)
			return (strdup(command));
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
