#include "main.h"

/**
 * runCommand - Runs the provided command
 * @argv: arguement vector array
 * Description: The executor takes and array of commands
 * and executes them
 * Return: The void
 */

void runCommand(char **argv)
{
	char *command = NULL;
	char *finalCommand = NULL;
	pid_t childProcess;
	int status;
	char *workingDir;
	char exitCode[10];

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

			workingDir = getcwd(NULL, 0);
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", workingDir, 1);
			free(workingDir);
			return;
		}
		else if (strcmp(command, "exit") == 0)
		{
			if (argv[1])
			{
				int exitStatus = atoi(argv[1]);
				exit(exitStatus);
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
		else
		{
			variableHandler(argv);
			finalCommand = getPath(command);
			childProcess = fork();
			if (childProcess == -1)
			{
				exit(EXIT_FAILURE);
			}
			if (childProcess == 0)
			{
				if (execve(finalCommand, argv, NULL) == -1)
				{
					printf("%s: No such file or directory\n", argv[0]);
				}
			}
			else
			{
				wait(&status);
				sprintf(exitCode, "%d", WEXITSTATUS(status));
				setenv("?", exitCode, 1);
				free(finalCommand);
			}
		}
	}
}
