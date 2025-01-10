#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

char **tokenizazion(char *input);
void execute_command(char *command, char **env);
char *custom_getenv(const char *name, char **env);
char *custom_which(char *command, char **env);
char *get_command_path(char *command, char **env);
void print_env(char **env);

#endif
