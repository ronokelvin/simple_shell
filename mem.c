#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if the pointer was freed, otherwise 0.
 */
int bfree(void **ptr)
{
	/** Check if the pointer is not NULL
	 * 		and points to a valid memory location */
	if (ptr && *ptr)
	{
		/* Free the memory pointed to by the pointer */
		free(*ptr);
		/* Set the pointer to NULL to avoid a dangling pointer */
		*ptr = NULL;
		return (1); /* Return 1 to indicate that the pointer was freed */
	}
	return (0); /* Return 0 to indicate that the pointer was not freed */
}
