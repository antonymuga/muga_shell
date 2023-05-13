void execute_command(char **args) {
    /* Execute the command */
    if (execve(args[0], args, NULL) == -1) {
        perror("Error executing command");
    }
}

int main(void) {
    char prompt[] = "alx_shell:$ ";
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    char **args;
    int num_tokens = 0;
    char *token;
    int i;

    while (1) {
        printf("%s", prompt);

        /* Use getline() to read input from the user */
        nchars_read = getline(&lineptr, &n, stdin);

        if (nchars_read == -1) {
            perror("Error reading input");
            return EXIT_FAILURE;
        }

        /* Split the string into an array of words */
        token = strtok(lineptr, delim);

        while (token != NULL) {
            num_tokens++;
            token = strtok(NULL, delim);
        }

        /* Allocate space to hold the array of strings */
        args = malloc(sizeof(char *) * (num_tokens + 1));

        /* Reset the lineptr and token variables for parsing */
        lineptr = strtok(lineptr, "\n");
        token = strtok(lineptr, delim);
        i = 0;

        while (token != NULL) {
            args[i] = strdup(token);
            token = strtok(NULL, delim);
            i++;
        }
        args[i] = NULL;

        /* Execute the command */
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error forking");
        } else if (pid == 0) {
            execute_command(args);
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }

        /* Free the allocated memory */
        for (i = 0; i < num_tokens; i++) {
            free(args[i]);
        }
        free(args);
        num_tokens = 0;
    }

    free(lineptr);
    return EXIT_SUCCESS;
}
