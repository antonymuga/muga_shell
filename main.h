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

void execmd(char **argv);
char *get_location(char *command);
int stat(const char *pathname, struct stat *statbuf);
/* void replace_variables(char **argv); */
char *replace_variables(char *command);

#endif