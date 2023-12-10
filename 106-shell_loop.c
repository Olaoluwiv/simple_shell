#include "shell.h"

/**
 * hsh - Main shell loop.
 * @name: Pointer to a structure of type 'data_t'
 * containing potential arguments.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(data_t *name, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(data);
		if (r != -1)
		{
			set_info(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (interactive(info))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(name);
	free_data(data, 1);
	if (!interactive(data) && data->status)
		exit(name->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Finds a builtin command.
 * @data: Pointer to a structure of type 'data_t'
 * containing potential arguments.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit().
 */
int find_builtin(data_t *data)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[i].func(data);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - Finds a command in PATH.
 * @name: Pointer to a structure of type 'data_t'
 *        containing potential arguments.
 *
 * This function searches for the command specified in the 'name' structure
 * within the directories listed in the PATH environment variable. If the
 * command is found, it forks a new process to execute the command.
 *
 * Return: Void.
 */
void find_cmd(data_t *name)
{
	char *path = NULL;
	int i, k;

	name->path = name->argv[0];
	if (name->linecount_flag == 1)
	{
		name->line_count++;
		name->linecount_flag = 0;
	}
	for (i = 0, k = 0; name->arg[i]; i++)
		if (!is_delim(name->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(name, _getenv(name "PATH="), name->argv[0]);
	if (path)
	{
		name->path = path;
		fork_cmd(name);
	}
	else
	{
		if ((interactive(name) || _getenv(name, "PATH=")
					|| name->argv[0][0] == '/') && is_cmd(name, name->argv[0]))
		{
			fork_cmd(name);
		}
		else if (*(name->arg) != '\n')
		{
			name->status = 127;
			print_error(name, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks a new process to execute a command.
 * @name: Pointer to a structure of type 'data_t'
 *        containing potential arguments.
 *
 * This function creates a child process using fork and executes a command in
 * the child process using execve. It waits for the child process to complete
 * and updates the status of the 'name' structure accordingly.
 *
 * Return: Void.
 */
void fork_cmd(data_t *name)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
