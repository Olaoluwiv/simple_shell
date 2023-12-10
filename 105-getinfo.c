#include "shell.h"

/**
 * clear_info - Initializes data_t struct.
 * @name: Pointer to a structure of type 'data_t' to be initialized.
 */
void clear_info(data_t *name)
{
	name->arg = NULL;
	name->argv = NULL;
	name->path = NULL;
	name->argc = 0;
}

/**
 * set_info - Initializes data_t struct.
 * @name: Pointer to a structure of type 'data_t' to be initialized.
 * @av: Argument vector.
 */
void set_info(data_t *name, char **av)
{
	int i = 0;

	name->fname = av[0];
	if (name->arg)
	{
		name->argv = strtow(name->arg, " \t");
		if (!name->argv)
		{
			name->argv = malloc(sizeof(char *) * 2);
			if (name->argv)
			{
				name->argv[0] = _strdup(name->arg);
				name->argv[1] = NULL;
			}
		}
		for (i = 0; name->argv && name->argv[i]; i++)
			;
		name->argc = i;

		replace_alias(name);
		replace_vars(name);
	}
}

/**
 * free_data - Frees data_t struct fields.
 * @name: Pointer to a structure of type 'data_t'.
 * @all: True if freeing all fields.
 */
void free_data(data_t *name, int all)
{
	ffree(name->argv);
	name->argv = NULL;
	name->path = NULL;
	if (all)
	{
		if (!name->cmd_buf)
			free(name->arg);
		if (name->env)
			free_list(&(name->env));
		if (name->history)
			free_list(&(name->history));
		if (name->alias)
			free_list(&(name->alias));
		ffree(name->environ);
		name->environ = NULL;
		bfree((void **)name->cmd_buf);
		if (name->readfd > 2)
			close(name->readfd);
		_putchar(BUF_FLUSH);
	}
}
