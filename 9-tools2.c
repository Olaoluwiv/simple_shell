#include "shell.h"

/**
 * is_positive_number - Check if a string represents a positive number.
 * @str: The input string to be checked.
 * Return: 1 if the string is a positive number, 0 otherwise.
 */
int is_positive_number(char *str)
{
	if (!str)
		return (0);

	for (int i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}

/**
 * _atoi - Convert a string to an integer.
 * @str: The input string to convert.
 *
 * Return: The integer value of the string.
 */
int _atoi(char *str)
{
	int num = 0;

	for (int i = 0; str[i]; i++)
	{
		num *= 10;
		num += (str[i] - '0');
	}

	return (num);
}
