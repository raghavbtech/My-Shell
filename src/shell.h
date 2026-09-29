#ifndef SHELL_H
#define SHELL_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

/* Prompt and input handling (shell.c) */
void print_prompt(void);
char *read_line(void);

/* Parsing (parse.c) */
char **parse_line(char *line);

/* Built-in commands (builtin.c) */
int handle_builtin(char **args);

/* Command execution (execute.c) */
int execute(char **args);

#endif /* SHELL_H */
