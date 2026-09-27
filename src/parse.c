#include "shell.h"

char **parse_line(char *line)
{
    static char *args[MAX_ARGS];
    int i = 0;

    char *token = strtok(line, " ");

    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}
