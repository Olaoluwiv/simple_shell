#include "shell.h"

/**
 * _getenv - Get the value of an environmental name
 * @variable: The name of the environmental variable
 *
 * Return: The value of the environmental name or NULL
 */
char *_getenv(const char *variable)
{
	char *tmp, *key, *value, *env;
	int m;

	for (m = 0; environ[m]; m++)
	{
		tmp = _strdup(environ[m]);
		key = strtok(tmp, "=");
		if (_strcmp(key, variable) == 0)
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
