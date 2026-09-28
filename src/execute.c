#include "shell.h"

int execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("myshell");
        return 1;
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "myshell: command not found: %s \n", args[0]);
            exit(1);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }

    return 1;
}
