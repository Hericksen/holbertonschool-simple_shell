#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_TOKENS 64

char **tokenize_input(char *input);
void free_args(char **args);
char *get_command_path(char *command);
void execute_command(char *command);

#endif
