#include "shell.h"

/**
 * _execute - Execute a command process
 * @command: the command to be executed
 * @argv: command argument
 * @idx: index of the command input
 *
 * Description: Executes the command, handles, forks, and waits.
 * Return: The exit status of the command
 */
int _execute(char **command, char **argv, int idx)
{
	char *full_cmd = _getpath(command[0]);
	pid_t child;
	int status;

	if (!full_cmd)
	{
		char *mssg = "Error retrieving the full command path";

		print_error(argv[0], command[0], idx, mssg);
		free_array2D(command);
		return (127);
	}

	child = fork();
	if (child == -1)
	{
		perror("fork");
		free(full_cmd);
		free_array2D(command);
		return (1);
	}

	if (child == 0)
	{
		if (execve(full_cmd, command, environ) == -1)
		{
			perror("execve");
			free(full_cmd);
			free_array2D(command);
			return (1);
		}
	}

	waitpid(child, &status, 0);
	free(full_cmd);
	free_array2D(command);
	return (WEXITSTATUS(status));
}
