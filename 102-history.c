#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(data_t *name)
{
	char *buf, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Creates a file, or appends to an existing file.
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.
 *
 * Return: 1 on success, else -1.
 */
int write_history(data_t *name)
{
	ssize_t fd;
	char *filename = get_history_file(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from file.
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.
 *
 * Return: Histcount on success, 0 otherwise.
 */
int read_history(data_t *name)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(name);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds entry to a history linked list.
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *name, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.
 *
 * Return: The new histcount.
 */
int renumber_history(data_t *name)
{
	list_t *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (name->histcount = i);
}
