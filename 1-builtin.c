#include "shell.h"

/**
 * is_builtin - check if the command is a builtin command
 * @command: the command to check
 *
 * Return: 1 if the command is builtin, otherwise 0
 */
int is_builtin(char *command)
{
	char *builtin[] = { "exit", "env", "setenv", "cd", NULL };
	int i;

	for (i = 0; builtin[i]; i++)
	{
		if (_strcmp(command, builtin[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * exit_shell - Handles the 'exit' built-in command.
 * @command: The command arguments.
 * @argv: The program's arguments.
 * @status: The exit status to be updated.
 * @idx: Index of the command in the input.
 *
 * If the 'exit' command is called with an argument, it attempts to convert
 * the argument to an integer and uses it as the exit status. If no argument
 * is provided or the argument is not a valid positive integer, an error
 * message is printed to STDERR, and the exit status is set to 2.
 */
void exit_shell(char **command, char **argv, int *status, int idx)
{
	int exit_value = (*status);
	char *index, mssg[] = ": exit illegal number";

	if (command[1])
	{
		if (is_positive_number(command[1]))
			exit_value = _atoi(command[1]);
	}
	else
	{
		index = _itoa(idx);
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, index, _strlen(index));
		write(STDERR_FILENO, mssg, _strlen(mssg));
		write(STDERR_FILENO, command[1], _strlen(command[1]));
		write(STDERR_FILENO, "\n", 1);
		free(index);
		free_array2D(command);
		(*status) = 2;
		return;
	}

	free_array2D(command);
	exit(exit_value);
}

/**
 * print_env - handle the 'env' built-in command
 * @command: The command and its arguments.
 * @status: the exit status update
 */
void print_env(char **command, int *status)
{
	int i;

	for (i = 0; environ[i]; i++)
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));

	write(STDOUT_FILENO, "\n", 1);

	free_array2D(command);
	(*status) = 0;
}
/**
 * handle_builtin - Handle execution of built-in shell commands.
 * @command: The command and its arguments.
 * @argv: The program's arguments.
 * @status: The exit status to update.
 * @idx: Index of the command in the input.
 */
void handle_builtin(char **command, char **argv, int *status, int idx)
{
	if (_strcmp(command[0], "exit") == 0)

		exit_shell(command, argv, status, idx);
	else if (_strcmp(command[0], "env") == 0)
		print_env(command, status);
	if (_strcmp(command[0], "exit") == 0)
		exit_shell(command, argv, status, idx);
	else if (_strcmp(command[0], "env") == 0)
		print_env(command, status);
}
