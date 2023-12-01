#iinclude "shell.h"
/**
 * _getpath - Get the full path of an executable command.
 * @commnd: The name of the command.
 * Return: The full path of the command, or NULL if not found.
 */
char *_getpath(char *commnd)
{
	char *path_env, *full_cmd, *dir;
	int m;
	struct stat st;

	for (m = 0; commnd[m]; m++)
	{
		if (commnd[m] == '/')
		{
			if (stat(commnd, &st) == 0)
				return (_strdup(commnd));
		return (NULL);
		}
	}

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	dir = strtok(path_env, ":");
	while (dir)
	{
		full_cmd = malloc(_strlen(dir) + _strlen(commnd) + 2);
		if (full_cmd)
		{
			_strcpy(full_cmd, dir);
			_strcat(full_cmd, "/");
			_strcat(full_cmd, commnd);
			if (stat(full_cmd, &st) == 0)
			{
				free(path_env);
				return (full_cmd);
			}
			free(full_cmd);
			dir = strtok(NULL, ":");
		}
	}
	free(path_env);
	return (NULL);
}
