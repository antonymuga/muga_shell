#include "main.h"

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

        /* added code for exit built-in */
        else if (strcmp(command, "exit") == 0)
        {
            /* exit the shell */
            exit(EXIT_SUCCESS);
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
