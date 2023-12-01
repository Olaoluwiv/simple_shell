#include "shell.h"

/**
 * _getenv - Get the value of an environmental variable
 * @variable: The name of the environmental variable
 *
 * Return: The value of the environmental variable or NULL
 */
char *_getenv(char *variable)
{
	char *key, *value, *env;
	int i;

	if (variable == NULL)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		char *tmp = _strdup(environ[i]);

		if (tmp == NULL)
			return (NULL);

		key = strtok(tmp, "=");

		if (key != NULL && _strcmp(key, variable) == 0)
		{
			value = strtok(NULL, "\n");
			env = (value != NULL) ? _strdup(value) : NULL;

			free(tmp);
			return (env);
		}

		free(tmp);
	}

	return (NULL);
}
