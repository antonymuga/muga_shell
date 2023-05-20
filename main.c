#include "main.h"

int main(int ac, char **argv)
{
    char *prompt = "alx_shell:$ ";
    char *lineptr = NULL; 
    char *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    int interactive;
    
    (void)ac;

   
    interactive = isatty(STDIN_FILENO);

    
    while (1)
    {
        
        if (interactive) {
            printf("%s", prompt);
        }

        nchars_read = getline(&lineptr, &n, stdin);
        
        if (nchars_read == -1)
        {
            if (feof(stdin)) {  
                printf("\n");
                return (0);
            }
            perror("getline");
            return (-1);
        }

       
        lineptr_copy = malloc(sizeof(char) * (nchars_read + 1));
        if (lineptr_copy == NULL)
        {
            perror("malloc");
            return (-1);
        }
        
        strcpy(lineptr_copy, lineptr);

        
        token = strtok(lineptr, delim);

        while (token != NULL)
        {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        
        argv = malloc(sizeof(char *) * num_tokens);

        
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++)
        {
            argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        execmd(argv);

        
        for (i = 0; i < num_tokens - 1; i++) {
            free(argv[i]);
        }
        free(argv);
        free(lineptr_copy);
        free(lineptr);
        lineptr = NULL;
        num_tokens = 0;

        
        if (!interactive) {
            return 0;
        }
    }

    return (0);
}
