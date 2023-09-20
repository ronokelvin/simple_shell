#include "shell.h"

/**
 * _erroratoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, or -1 on error.
 */
int _erroratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	/* Handle leading '+' sign, if present */
	if (*s == '+')
		s++;

	/* Convert the string to an integer */
	for (i = 0; s[i] != '\0'; i++)
	{
		/* Check if the character is a valid digit */
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');

			/* Check for integer overflow */
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * print_error - Prints an error message to the standard error.
 * @info: Pointer to the parameter & return info struct.
 * @estr: String containing the specified error type.
 *
 * Return: Returns nothing.
 */
void print_error(info_t *info, char *estr)
{
	_inputs(info->fname);
	_inputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_inputs(": ");
	_inputs(info->argv[0]);
	_inputs(": ");
	_inputs(estr);
}

/**
 * print_d - Function prints a decimal (integer) number (base 10).
 * @input: The input number to print.
 * @fd: The file descriptor to write to (STDOUT_FILENO or STDERR_FILENO).
 *
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	/* Use _inputchar instead of _putchar for STDERR */
	if (fd == STDERR_FILENO)
		__putchar = _inputchar;

	/* Handle negative numbers */
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;

	/* Print each digit of the number */
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	/* Print the last digit */
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to a string representation in the given base.
 * @num: The number to be converted.
 * @base: The base for conversion.
 * @flags: Argument flags to control conversion behavior.
 *
 * Return: A string representation of the number in the specified base.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	/* Handle signed number */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	/* Convert the number to the specified base */
	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	/* Add the sign if applicable */
	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_comments(char *buf)
{
	int i;

	/* Find the first '#' preceded by a space and replace it with '\0' */
	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
