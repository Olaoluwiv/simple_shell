#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @name: Unused data_t struct parameter.
 * @path: Path to the file.
 *
 * This function checks if the file specified by the given path
 * is an executable command.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(data_t *name, char *path)
{
	struct stat st;

	(void)name;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @name: Unused data_t struct parameter.
 * @pathstr: The PATH string containing directories separated by colons.
 * @cmd: The command to find in the PATH directories.
 *
 * This function searches for the given command in the directories
 * specified by the PATH string. It checks both the current directory
 * and directories listed in PATH to find the full path of the command.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */
char *find_path(data_t *name, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(name, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
