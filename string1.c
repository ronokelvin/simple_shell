#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	/* Check if the input string is NULL */
	if (str == NULL)
		return (NULL);

	/* Calculate the length of the input string */
	while (*str++)
		length++;

	/* Allocate memory for the duplicated string (+1 for null terminator) */
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	/* Copy the characters from the input string to the duplicated string */
	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * starts_with - Checks if the substring needle
 * starts with the string haystack.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack if needle is found/NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	/* Iterate through both strings until the end of needle is reached */
	while (*needle)
	{
		/* If characters are different, needle is not a prefix of haystack */
		if (*needle++ != *haystack++)
			return (NULL);
	}

	/* If needle is found,return the address of the next character in haystack */
	return ((char *)haystack);
}

/**
 * _puts - Prints an input string to the standard output (stdout).
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int i = 0;

	/* Check if the input string is NULL */
	if (!str)
		return;

	/* Print each character of the string until reaching the null terminator */
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes the character 'c' to the standard output (stdout).
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno appropriately.
 */
int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;
	/* Check if the character is the buffer flush symbol or buffer is full */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/* Write the buffer to stdout and reset the buffer index */
		write(1, buf, i);
		i = 0;
	}

	/* Check if the character is not the buffer flush symbol */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
