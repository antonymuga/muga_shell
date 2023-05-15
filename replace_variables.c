#include "main.h"


char *replace_variables(char *command)
{
    char *new_command = NULL;
    char *p;
    int pid = getpid();
    int len;

    /* Replace all occurrences of $$ with the PID */
    if ((p = strstr(command, "$$")))
    {
        len = strlen(command) - strlen(p);
        if (asprintf(&new_command, "%.*s%d%s", len, command, pid, p + 2) == -1)
        {
            perror("asprintf");
            return command;
        }
    }
    else
    {
        new_command = strdup(command);
        if (!new_command)
        {
            perror("strdup");
            return command;
        }
    }

    /* Replace all occurrences of $? with the exit status of the last command */
    if ((p = strstr(new_command, "$?")))
    {
        len = strlen(new_command) - strlen(p);
        if (asprintf(&p, "%d", last_exit_status) == -1)
        {
            perror("asprintf");
            return new_command;
        }
        p[len] = '\0';
    }

    /* Free the memory allocated by asprintf if it was used */
    if (new_command != command)
    {
        free(command);
    }

    return new_command;
}
