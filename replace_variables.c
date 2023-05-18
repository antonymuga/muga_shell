#include "main.h"

void replace_variables(char **argv)
{
    int i;
    char pid_str[10];
    char *env_val;

    for (i = 0; argv[i] != NULL; i++)
    {
        if (argv[i][0] == '$')
        {
            if (strcmp(argv[i], "$$") == 0)
            {
                sprintf(pid_str, "%d", getpid());
                free(argv[i]);
                argv[i] = strdup(pid_str);
            }
            else if (strcmp(argv[i], "$?") == 0)
            {
                env_val = getenv("?");
                if (env_val != NULL)
                {
                    free(argv[i]);
                    argv[i] = strdup(env_val);
                }
                else
                {
                    free(argv[i]);
                    argv[i] = strdup("");
                }
            }
            else
            {
            }
        }
    }
}
