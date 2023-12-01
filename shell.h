#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>



#define Delim "*\n"

char *read_line(void);
char **tokenizer(char  *line);
extern char **environ;
void print_error(char *name, char *cmd, int idx, char *mssg);

char *_getpath(char *command);
char *_get_env(char *variable);
int _execute(char **command, char **argv, int idx);
int is_positive_number(char *str);
int _atoi(char *str);

char  *_itoa(int o);

/**************tools.c*****************/
void free_array2D(char  **array);
void print_error(char *name, char *cmd, int idx, char *mssg);
char *_itoa(int n);
void reverse_string(char *str, int len);

/****************string.c******************/
int _strlen(char *s);
char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, const char *src);

/***************builtin.c******************/
void handle_builtin(char **command, char **argv, int *status, int idx);
void exit_shell(char **command, char **argv, int *status, int idx);
void print_env(char **command, int *status);
int ls_builtin(char *command);

#endif
