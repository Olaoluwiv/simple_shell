#include "shell.h"

/**
 * _myenv - Prints the current environment.
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.Used to maintain a constant function
 * prototype.
 *
 * Return: Always returns 0.
 */
int _myenv(data_t *name)
{
	print_list_str(name->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @name: Pointer to a null-terminated string representing
 * the environment variable name.
 * Return: Returns the value of the environment variable if found;
 * otherwise, returns NULL.
 */
char *_getenv(const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable or modifies
 * an existing one.
 * @name: Pointer to a structure of type 'data_t' containing potential
 * arguments.
 *        Used to maintain a constant function prototype.
 * Return: Returns 0 on success; otherwise, returns 1.
 */
int _mysetenv(data_t *name)
{
	if (name->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(name, name->argv[1], name->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable.
 * @name: Pointer to a structure of type 'data_t' containing potential
 * arguments.Used to maintain a constant function prototype.
 * Return: Always returns 0.
 */
int _myunsetenv(data_t *name)
{
	int i;

	if (name->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= name->argc; i++)
		_unsetenv(name, name->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list
 * @name: Pointer to a structure of type 'data_t' containing
 * potential arguments.
 *        Used to maintain a constant function prototype.
 * Return: Always returns 0.
 */
int populate_env_list(data_t *name)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	name->env = node;
	return (0);
}
