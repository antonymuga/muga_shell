#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>

extern char **environ;

void runCommand(char **argv);
char *getPath(char *command);
int stat(const char *pathname, struct stat *statbuf);
void variableHandler(char **argv);

#endif
