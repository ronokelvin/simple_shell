#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area to be filled.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 *
 * Description: This function fills the first n bytes of the memory area
 * pointed to by s with the constant byte b.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	/* Loop through the first n bytes of memory area s */
	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: Pointer to a string of strings.
 *
 * This function frees the memory allocated for each string in the array
 * and then frees the memory allocated for the array itself.
 */
void ffree(char **pp)
{
	char **a = pp;

	/* If pp is NULL, there is nothing to free, so return */
	if (!pp)
		return;

	/* Free each string in the array */
	while (*pp)
		free(*pp++);

	/* Free the memory allocated for the array */
	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the new allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	/* If ptr is NULL, it is equivalent to malloc(new_size) */
	if (!ptr)
		return (malloc(new_size));

	/* If new_size is 0, free the memory block and return NULL */
	if (!new_size)
		return (free(ptr), NULL);

	/* If new_size is equal to old_size, return the original pointer */
	if (new_size == old_size)
		return (ptr);

	/* Allocate memory for the new block */
	p = malloc(new_size);
	if (!p)
		return (NULL);

	/* Copy the old data to the new block */
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	/* Free the old memory block and return the new pointer */
	free(ptr);
	return (p);
}
