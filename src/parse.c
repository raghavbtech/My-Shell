#include "shell.h"

char **parse_line(char *line)
{
    static char *args[MAX_ARGS];
    int i = 0;
    char *save_inner;

    char *token = strtok_r(line, " ", &save_inner);

    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok_r(NULL, " ", &save_inner);
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
