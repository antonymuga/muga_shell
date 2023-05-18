#include "main.h"

char *get_location(char *command)
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);

    char *path_token = strtok(path_copy, ":");
    char *file_path = NULL;

    while (path_token != NULL)
    {
        file_path = malloc(strlen(path_token) + strlen(command) + 2);
        strcpy(file_path, path_token);
        strcat(file_path, "/");
        strcat(file_path, command);

        if (access(file_path, X_OK) == 0)
        {
            free(path_copy);
            return file_path;
        }
        else
        {
            free(file_path);
            path_token = strtok(NULL, ":");
        }
    }

    free(path_copy);

    if (access(command, X_OK) == 0)
    {
        return strdup(command);
    }

    return NULL;
}
