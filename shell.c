#include"shell.h"
/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 or 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 or 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 or 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0
 */
int _atoi(char *s)
{
	int a, sin = 1, fg = 0, out;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && fg != 2; a++)
	{
		if (s[a] == '-')
			sin *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sin == -1)
		out = -result;
	else
		out = result;

	return (out);
}
