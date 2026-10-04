#include "shell.h"

int main(void)
{
    char *line;
    char *command;
    char *save_outer;
    char **args;

    while (1)
    {
        print_prompt();
        line = read_line();
        command = strtok_r(line, ";", &save_outer);
        while (command != NULL)
        {
            while (*command == ' ')
            {
                command++;
            }

            args = parse_line(command);
            execute(args);

            command = strtok_r(NULL, ";", &save_outer);
        }
    }

    return 0;
}

void print_prompt(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("myshell:%s> ", cwd);
    }
    else
    {
        printf("myshell> ");
    }
    fflush(stdout);
}

char *read_line(void)
{
    static char line[MAX_LINE];

    if (fgets(line, MAX_LINE, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }

    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) > 0 && history_count < MAX_HISTORY)
    {
        history[history_count] = strdup(line);
        history_count++;
    }

    return line;
}