#include "shell.h"
/**
 * tokenizer - Tokenize a string into an array of tokens.
 * @line: The input string to tokenize.
 * Return: An array of token strings or NULL on failure.
 */
char **tokenizer(char *line)
{
	char *token = NULL, *tmp = NULL;
	char **command = NULL;
	int cpt = 0, i = 0;

	if (!line)
		return (NULL);

	tmp = strdup(line);

	token = strtok(tmp, Delim);

	while (token)
	{
		cpt++;
		token = strtok(NULL, Delim);
	}

	free(tmp);

	command = (char **)malloc(sizeof(char *) * (cpt + 1));
	token = strtok(line, Delim);

	while (token)
	{
		command[i] = token;
		token = strtok(NULL, Delim);
		i++;
	}

	free(line);

	command[i] = NULL;

	return (command);
}
