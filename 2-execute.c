#include "shell.h"

/**
 * _execute - Execute a command and handle errors.
 *
 * @command: Array of strings representing the command and its arguments.
 * @argv: Array of strings representing the program's arguments.
 * @idx: Index of the command in the input.
 *
 * Return: Exit status of the command execution.
 */
int _execute(char **command, char **argv, int idx)
{
	char *full_cmd;
	pid_t child;
	int status;

	full_cmd = _getpath(command[0]);

	if (!full_cmd)
	{
		print_error(argv[0], command[0], idx);
		free_array2D(command);
		return (127);
	}
	child = fork();
	if (child == 0)
	{
		if (execve(full_cmd, command, environ) == -1)
		{
			free(full_cmd);
			free_array2D(command);
		}
	}
	else
	{
		waitpid(child, &status, 0);
		free_array2D(command);
		free(full_cmd), full_cmd = NULL;
	}
	return (WEXITSTATUS(status));
}
