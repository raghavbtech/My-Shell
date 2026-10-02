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

void expand_variables(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] == '$')
        {
            char *var_name = args[i] + 1;
            char *value = getenv(var_name);
            if (value != NULL)
            {
                args[i] = value;
            }
            else
            {
                args[i] = "";
            }
        }
    }
}
