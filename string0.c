#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	/* Move the pointer dest to the end of the string */
	while (*dest)
		dest++;

	/* Copy the characters from src to the end of dest */
	while (*src)
		*dest++ = *src++;

	/* Add null terminator to the concatenated string */
	*dest = '\0';

	/* Return the pointer to the beginning of the concatenated string */
	return (ret);
}

/**
 * my_strlen - Returns the length of a string.
 * @s: The string whose length to check.
 *
 * Return: Integer length of the string.
 */
int my_strlen(char *s)
{
	int length = 0;

	/* Check if the input string is NULL */
	if (!s)
		return (0);

	/* Increment the length until reaching the null terminator '\0' */
	while (*s++)
		length++;

	return (length);
}

/**
 * my_strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		/* Move to the next character in both strings */
		s1++;
		s2++;
	}

	/* Check if both strings are equal */
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	/* Check if the destination and source are the same or if src is NULL */
	if (dest == src || src == 0)
		return (dest);

	/* Copy characters from source to destination */
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	/* Add null terminator to the copied string */
	dest[i] = '\0';

	return (dest);
}
