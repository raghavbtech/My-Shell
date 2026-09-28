#include "shell.h"

int main(void)
{
    char *line;
    char **args;

    while (1)
    {
        print_prompt();
        line = read_line();
        args = parse_line(line);
        execute(args);
    }

    return 0;
}

void print_prompt(void)
{
    printf("myshell> ");
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

    return line;
}
