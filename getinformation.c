#include "shell.h"

/**
 * clear_info - Clears the fields of the info_t struct.
 * @info: Pointer to the info_t struct.
 */
void clear_info(info_t *info)
{
	/* Set the 'arg' field to NULL, clearing any stored input string */
	info->arg = NULL;
	/* Set the 'argv' field to NULL, clearing any stored argument tokens */
	info->argv = NULL;
	/* Set the 'path' field to NULL, clearing any stored path value */
	info->path = NULL;
	/* Set the 'argc' field to 0, indicating no arguments are stored */
	info->argc = 0;
}

/**
 * set_info - Initializes the info_t struct.
 * @info: Pointer to the info_t struct.
 * @av: Argument vector (command-line arguments).
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	/* Set the 'fname' field to the name of the program*/
	/*	 (first element of the argument vector) */
	info->fname = av[0];

	if (info->arg)
	{
		/* Split the 'arg' string into tokens */
		/*	and store them in the 'argv' field */
		info->argv = split_string(info->arg, " \t");

		if (!info->argv)
		{
			/* If split_string fails, allocate memory for 'argv' */
			/*	and store the original 'arg' as a single element */
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		/* Count the number of elements in 'argv' */
		/*	to get the argument count 'argc' */
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		/* Replace any aliases in the arguments with their */
		/*	corresponding values */
		replace_alias(info);

		/* Replace any environment variables in the */
		/*arguments with their corresponding values */
		replace_vars(info);
	}
}

/**
 * free_info - Frees fields in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: True if freeing all fields, false otherwise.
 */
void free_info(info_t *info, int all)
{
	/* Free the 'argv' field and set it to NULL */
	ffree(info->argv);
	info->argv = NULL;

	/* Set 'path' field to NULL */
	info->path = NULL;

	if (all)
	{
		/* Free additional fields if 'all' is true */

		if (!info->cmd_buf)
			free(info->arg); /* Free 'arg' field if 'cmd_buf' is not set */

		if (info->env)
			free_list(&(info->env)); /* Free the 'env' linked list */

		if (info->history)
			free_list(&(info->history)); /* Free the 'history' linked list */

		if (info->alias)
			free_list(&(info->alias)); /* Free the 'alias' linked list */

		ffree(info->environ); /* Free the 'environ' field and set it to NULL */
		info->environ = NULL;

		bfree((void **)info->cmd_buf); /* Free the command buffer using bfree */

		if (info->readfd > 2)
		{
			/* Close the read file descriptor if it is greater than 2 */
			close(info->readfd);
		}
			
		_putchar(BUF_FLUSH); /* Flush the buffer */

		/* All other fields will be freed automatically when the struct is deallocated */
	}
}
