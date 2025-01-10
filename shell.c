#include "shell.h"

int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_size;

	(void)argc;
	(void)argv;

	while (1)
	{
		/* Affichage du prompt si entrée interactive */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Lecture de l'entrée utilisateur */
		read_size = getline(&input, &input_size, stdin);
		if (read_size == -1) /* Fin du fichier ou erreur */
		{
			if (isatty(STDIN_FILENO)) /* Si mode interactif, afficher un message */
				write(STDOUT_FILENO, "\nExiting shell...\n", 18);
			free(input);
			_exit(EXIT_SUCCESS);
		}

		/* Suppression du saut de ligne */
		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0';

		/* Commande "exit" */
		if (strcmp("exit", input) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		/* Commande "env" */
		if (strcmp("env", input) == 0)
		{
			print_env(env);
			continue; /* Retour au début de la boucle */
		}

		/* Commande "which" */
		if (strncmp("which", input, 5) == 0)
		{
			char *command = input + 6; /* Skip "which " (5 caractères + espace) */
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
			continue; /* Retour au début de la boucle */
		}

		/* Exécution d'autres commandes */
		execute_command(input, env);
	}

	free(input);
	_exit(0); /* Ajout d'un _exit pour éviter tout comportement indéfini */
}
