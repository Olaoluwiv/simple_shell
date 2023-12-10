#include "shell.h"

/**
 * is_chain - Tests if the current char in buffer is a chain delimiter.
 * @name: Pointer to a structure of type 'data_t'
 * containing potential arguments.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(data_t *name, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		name->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* Found end of this command */
	{
		buf[j] = 0; /* Replace semicolon with null */
		name->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on last status.
 * @name: Pointer to a structure of type 'data_t'
 * containing potential arguments.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(data_t *name, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @name: Pointer to a structure of type 'data_t'
 * containing potential arguments.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(data_t *name)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(name->alias, name->argv[0], '=');
		if (!node)
			return (0);
		free(name->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		name->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces vars in the tokenized string.
 * @name: Pointer to a structure of type 'data_t'
 * containing potential arguments.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(data_t *name)
{
	int i = 0;
	list_t *node;

	for (i = 0; name->argv[i]; i++)
	{
		if (name->argv[i][0] != '$' || !name->argv[i][1])
			continue;

		if (!_strcmp(name->argv[i], "$?"))
		{
			replace_string(&(name->argv[i]),
				_strdup(convert_number(name->status, 10, 0)));
			continue;
		}
		if (!_strcmp(name->argv[i], "$$"))
		{
			replace_string(&(name->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(name->env, &name->argv[i][1], '=');
		if (node)
		{
			replace_string(&(name->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&name->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replaces string.
 * @old: Address of old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
