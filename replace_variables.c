#include "main.h"

void replace_variables(char **argv)
{
    int i;
    char pid_str[10];

    for (i = 0; argv[i] != NULL; i++)
    {
        /* check if the argument starts with $ */
        if (argv[i][0] == '$')
        {
            /* check if it's the $$ variable */
            if (strcmp(argv[i], "$$") == 0)
            {
                sprintf(pid_str, "%d", getpid());
                argv[i] = pid_str;
            }
            /* check if it's the $? variable */
            else if (strcmp(argv[i], "$?") == 0)
            {
                argv[i] = getenv("?");
            }
            /* handle other variables here */
            else
            {
                /* ... */
            }
        }
    }
    free(i);
}