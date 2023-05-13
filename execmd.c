#include "main.h"

extern char **environ;

void execmd(char **argv)
{
    char *command = NULL, *actual_command = NULL;
    pid_t child_pid;
    int status;

    if (argv)
    {
        /* get the command */
        command = argv[0];

        /* check if it's a built-in command */
        if (strcmp(command, "cd") == 0)
        {
            /* change directory */
            if (chdir(argv[1]) == -1)
            {
                perror("Error:");
            }
            return;
        }
        else if (strcmp(command, "exit") == 0)
        {
            /* exit the shell */
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
            /* print the environment variables */
            char **env = environ;
            while (*env)
            {
                printf("%s\n", *env++);
            }
            return;
        }

        /* generate the path to this command before passing it to execve */
        actual_command = get_location(command);
        
        /* create child process */
        child_pid = fork();
        if (child_pid == -1)
        {
            exit(EXIT_FAILURE);
        }
        /* execute the actual command with execve */
        if (child_pid == 0)
        {
            if (execve(actual_command, argv, NULL) == -1)
            {
                perror("Error:");
            }
        }
        else
        {
            wait(&status);
        }
    }
}
