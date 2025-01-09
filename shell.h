#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_TOKENS 100
#define MAX_PATH_LENGTH 1024

char **tokenizazion(char *input);
void execute_command(char *command, char **env);
void fork_and_execute(char **args, char *path, char **env);
char *custom_getenv(char *name, char **env);
char *custom_which(char *command, char **env);
char *get_command_path(char *command, char **env);
void print_env(char **env);
void handle_which_command(char *input, char **env);

#endif
