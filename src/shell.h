#ifndef SHELL_H
#define SHELL_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

/* Prompt and input handling (shell.c) */
void print_prompt(void);
char *read_line(void);

#endif /* SHELL_H */
