#include "shell.h"

int handle_redirection(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "myshell: expected filename after >\n");
                return -1;
            }
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("myshell");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            return 0;
        }

        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "myshell: expected filename after <\n");
                return -1;
            }
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                perror("myshell");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
            return 0;
        }
    }
    return 0;
}

int execute(char **args)
{
    expand_variables(args);
    if (handle_builtin(args))
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
        if (handle_redirection(args) == -1)
        {
            exit(1);
        }
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
