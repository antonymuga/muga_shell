#include "main.h"

/**
 * getPath - Gets the path of a command
 * @command: the command of whose path
 * we are trying to extract
 * Description: Find the path os a given command
 * Return: a string value for the path
 */

char *getPath(char *command)
{
	char *commandPath;
	char *pathDuplicate;
	char *pathToken;
	char *filePath;
	int commandLength;
	int directoryLength;
	struct stat buffer;

	commandPath = getenv("PATH");

	if (commandPath)
	{
		pathDuplicate = strdup(commandPath);
		commandLength = strlen(command);
		pathToken = strtok(pathDuplicate, ":");

		while (pathToken != NULL)
		{
			directoryLength = strlen(pathToken);
			filePath = malloc(commandLength + directoryLength + 2);
			strcpy(filePath, pathToken);
			strcat(filePath, "/");
			strcat(filePath, command);
			strcat(filePath, "\0");

			if (stat(filePath, &buffer) == 0)
			{
				free(pathDuplicate);
				return (filePath);
			}
			else
			{
				free(filePath);
				pathToken = strtok(NULL, ":");
			}
		}

		free(pathDuplicate);

		if (stat(command, &buffer) == 0)
		{
			return (strdup(command));
		}

		return (NULL);
	}

	return (NULL);
}
