#include "shell.h"
/**
 * free_args - Frees the argument array
 * @args: The argument array to free
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
