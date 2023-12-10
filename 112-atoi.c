#include "shell.h"

/**
 * interactive - Returns true if the shell is in interactive mode.
 * @name: Pointer to a data_t struct.
 *
 * This function checks if the shell is in interactive mode by verifying
 * if the standard input is a terminal and if the read file descriptor is
 * less than or equal to 2 (common file descriptors for stdin, stdout, stderr).
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(data_t *name)
{
	return (isatty(STDIN_FILENO) && name->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * This function iterates through the delimiter string to check if the
 * given character is a delimiter.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks for an alphabetic character.
 * @c: The character to check.
 *
 * This function checks if the given character is an alphabetic character.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * This function converts a string to an integer, considering sign and
 * stopping the conversion if a non-digit character is encountered.
 *
 * Return: 0 if no numbers in the string, converted number otherwise.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
