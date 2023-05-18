#include "main.h"

extern char **environ;

void execmd(char **argv)
{
    char *command = NULL;
    char *actual_command = NULL;
    pid_t child_pid;
    int status;
    char *cwd;
    char exit_code_str[10];

    if (argv)
    {
        command = argv[0];

        if (command[0] == '#')
        {
            return;
        }

        if (strcmp(command, "cd") == 0)
        {
            if (argv[1])
            {
                if (strcmp(argv[1], "-") == 0)
                {
                    if (chdir(getenv("OLDPWD")) == -1)
                    {
                        perror("Error:");
                    }
                }
                else
                {
                    if (chdir(argv[1]) == -1)
                    {
                        perror("Error:");
                    }
                }
            }
            else
            {
                if (chdir(getenv("HOME")) == -1)
                {
                    perror("Error:");
                }
            }

            cwd = getcwd(NULL, 0);
            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", cwd, 1);
            free(cwd);
            return;
        }
        else if (strcmp(command, "exit") == 0)
        {
            if (argv[1])
            {
                int exit_status = atoi(argv[1]);
                exit(exit_status);
            }
            else
            {
                exit(EXIT_SUCCESS);
            }
        }
        else if (strcmp(command, "env") == 0)
        {
            char **env = environ;
            while (*env)
            {
                printf("%s\n", *env++);
            }
            return;
        }
        else if (strcmp(command, "setenv") == 0)
        {
            if (argv[1] && argv[2])
            {
                if (setenv(argv[1], argv[2], 1) == -1)
                {
                    perror("Error:");
                }
            }
            else
            {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            }
            return;
        }
        else if (strcmp(command, "unsetenv") == 0)
        {
            if (argv[1])
            {
                if (unsetenv(argv[1]) == -1)
                {
                    perror("Error:");
                }
            }
            else
            {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            }
            return;
        }
        else if (strcmp(command, "&&") == 0)
        {
            if (argv[1])
            {
                /* Execute the left command */
                execmd(argv + 1);

                /* If the left command succeeded, execute the right command */
                if (strcmp(getenv("?"), "0") == 0)
                {
                    execmd(argv + 2);
                }
            }
            else
            {
                fprintf(stderr, "Invalid usage of '&&' operator\n");
            }
            return;
        }
        else if (strcmp(command, "||") == 0)
        {
            if (argv[1])
            {
                /* Execute the left command */
                execmd(argv + 1);

                /* If the left command failed, execute the right command */
                if (strcmp(getenv("?"), "0") != 0)
                {
                    execmd(argv + 2);
                }
            }
            else
            {
                fprintf(stderr, "Invalid usage of '||' operator\n");
            }
            return;
        }
        else
        {
            replace_variables(argv);

            actual_command = get_location(command);

            child_pid = fork();
            if (child_pid == -1)
            {
                exit(EXIT_FAILURE);
            }

            if (child_pid == 0)
            {
                if (execve(actual_command, argv, NULL) == -1)
                {
                    printf("%s: No such file or directory\n", argv[0]);
                    /* ... */
                }
            }
            else
            {
                wait(&status);
                sprintf(exit_code_str, "%d", WEXITSTATUS(status));
                setenv("?", exit_code_str, 1);
                free(actual_command);
            }
        }
    }
}
