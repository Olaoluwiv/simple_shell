#include "shell.h"

/**
 * main - simple shell function entry point
 * @ac: count of arguments line
 * @av: Arguments line
 * Return: 0 Always (success);
 */
int main(int ac, char **av)
{
	char *line = NULL, *command = NULL;
	int status = 0, idx = 0;

	(void)ac;
	(void)av;

	while (1)
	{
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);

			return (status);
		}
		idx++;

		command = tokenizer(line);

		if (!command)
			continue;

		if (ls_builtin(command))
			handle_builtin(command, av, &status, idx);
		else
		{
			status = _execute(command, av, idx);
		}

		free(line);
		free(command);
	}

	return (0);
}
