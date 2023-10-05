#include "shell.h"
/**
 * interactive_mode - shell is  in interactive mode.
 * @info: the address of the struct.
 *
 * Return: returns 1 if shell is interactive mode.
 * 	returns 0 if otherwise.
 */
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <=2);
}

/**
 * is_delimiter - check if character is delimiter.
 * @c: the character to be checked.
 * @delimiter: delimiter string.
 *
 * Return: returns 1 if true and 0 if false.
 */
int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
		{
			return (1);
		}
	return (0);
}

/**
 * is_alphabet - check if character is an alphabet.
 * @c: the character to be checked.
 *
 * Return: returns 1 if true and 0 if false.
 */
int is_alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * my_atoi - convert a string to an integer
 * @str: the string to be converted
 *
 * Return: returns 0 if there is no numbers in string,
 *			else returns the converted number.
 */

int my_atoi(char *str)
{
	int index, sign = 1, flag = 0, value;
	unsigned int result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		value = -result;
	else
		value = result;

	return (value);
}
