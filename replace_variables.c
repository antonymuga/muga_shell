#include "main.h"

void replace_variables(char **argv)
{
    int i;
    char pid_str[10];
    char *env_val;

    for (i = 0; argv[i] != NULL; i++)
    {
    /* check if the argument starts with $ */
    if (argv[i][0] == '$')
    {
        /* check if it's the $$ variable */
        if (strcmp(argv[i], "$$") == 0)
        {
            sprintf(pid_str, "%d", getpid());
            free(argv[i]);
            argv[i] = strdup(pid_str);
        }
        /* check if it's the $? variable */
        else if (strcmp(argv[i], "$?") == 0)
        {
            env_val = getenv("?");
            free(argv[i]);
            if (env_val != NULL)
            {
                argv[i] = strdup(env_val);
            }
            else
            {
                argv[i] = strdup("");
            }
        }
        /* handle other variables here */
        else
        {
            /* ... */
        }
    }
}
}
