#include "shell.h"

int handle_builtin(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "myshell: expected argument to \"cd\" \n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("myshell");
            }
        }
        return 1;
    }

    if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s \n", cwd);
        }
        else
        {
            perror("myshell");
        }
        return 1;
    }

    if (strcmp(args[0], "help") == 0)
    {
        printf("myshell - a simple Unix shell \n");
        printf("Built-in commands: \n");
        printf("  cd  <dir>   change directory\n");
        printf("  pwd         print current directory\n");
        printf("  clear       clear the screen\n");
        printf("  help        show this help message\n");
        printf("  exit        exit the shell \n");
        printf("Any other input is run as an external program. \n");
        return 1;
    }

    if (strcmp(args[0], "clear") == 0)
    {
        printf("\033[H\033[J");
        fflush(stdout);
        return 1;
    }

    return 0;
}
