#include "shell.h"

/**
 * _strncpy - Copies a string up to a given length.
 * @dest: The destination string to be copied to.
 * @src: The source string to be copied.
 * @n: The number of characters to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	/* Copy characters from source to destination up to n characters */
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	/* Fill the remaining characters in destination with null bytes ('\0') */
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * _strncat - Concatenates two strings up to a given length.
 * @dest: The first string (destination).
 * @src: The second string (source).
 * @n: The maximum number of bytes to be used from src.
 *
 * Return: A pointer to the concatenated string (dest).
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	/* Find the end of the destination string */
	i = 0;
	while (dest[i] != '\0')
		i++;

	/* Append characters from src to dest up to n characters */
	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* Null-terminate the concatenated string */
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the memory area of 's' where 'c' is found,
 *         or NULL if 'c' is not present in 's'.
 */
char *_strchr(char *s, char c)
{
	/* Iterate through the string until the character 'c' is found */
	do
	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	/* Return NULL if 'c' is not present in 's' */
	return (NULL);
}
