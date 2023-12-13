#include "shell.h"
/**
 * _execute - Execute a command.
 * @commnd: An array of command arguments.
 * @argv: An array of program arguments.
 * @idx: Index of the command in the input.
 * Return: The exit status of the command.
 */

int _execute(char **commnd, char **argv, int idx)
{
	char *full_cmd;
	pid_t child;
	int status;

	full_cmd = _getpath(commnd[0]);

	if (!full_cmd)
	{
		print_error(argv[0], commnd[0], idx);
		freearray2D(commnd);
		return (127);
	}
	child = fork();
	if (child == 0)
	{
		if (execve(full_cmd, commnd, environ) == -1)
		{
			free(full_cmd);
			freearray2D(commnd);
		}
	}
	else
	{
		waitpid(child, &status, 0);
		freearray2D(commnd);
		free(full_cmd), full_cmd = NULL;
	}
	return (WEXITSTATUS(status));
}
