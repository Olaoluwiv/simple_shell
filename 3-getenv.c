#include "shell.h"

/**
 * _getenv - Get the value of an environmental name
 * @name: The name of the environmental name
 *
 * Return: The value of the environmental name or NULL
 */
char *_getenv(const char *name)
{
	char *tmp, *key, *value, *env;
	int m;

	for (m = 0; environ[m]; m++)
	{
		tmp = _strdup(environ[m]);
		key = strtok(tmp, "=");
		if (_strcmp(key, name) == 0)
		{
			value = strtok(NULL, "\n");
			env = _strdup(value);
			free(tmp);
			return (env);
		}
		free(tmp);
	}
	return (NULL);
}
