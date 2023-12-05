#include "shell.h"

/**
 * _getenv - Get the value of an environmental name
 * @name: The name of the environmental name
 *
 * Return: The value of the environmental name or NULL
 */
char *_getenv(const char *name)
{
	char *key, *value, *env;
	int i;

	if (name == NULL)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		char *tmp = _strdup(environ[i]);

		if (tmp == NULL)
			return (NULL);

		key = strtok(tmp, "=");

		if (key != NULL && _strcmp(key, name) == 0)
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
