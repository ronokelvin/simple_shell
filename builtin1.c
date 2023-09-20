#include "shell.h"

/**
 * my_history - Displays the history list, one command per line, preceded
 *              by line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int my_history(info_t *info)
{
	/* Call the 'print_list' function to display the history list. */
	print_list(info->history);
	/* Return 0 to indicate successful execution. */
	return (0);
}

/**
 * unset_alias - Unsets an alias.
 * @info: The parameter struct.
 * @str: The string representing the alias to be unset in the format "alias_name".
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	/* Find the position of the equal sign '=' in the alias string. */
	p = _strchr(str, '=');
	if (!p)
	{
		/* If there is no equal sign, return error (1). */
		return (1);
	}

	/* Store the character after the equal sign (alias value) in 'c'. */
	c = *p;
	/* Replace the equal sign with the null terminator 
		to separate the alias name. */
	*p = 0;

	/* Get the index of the alias in the alias list using 'get_node_index'. */
	ret = delete_node_at_index(&(info->alias),
							   get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	/* Restore the equal sign character back to 
	its original position in 'str'. */
	*p = c;

	return (ret); /* Return 0 on success, 1 on error. */
}

/**
 * set_alias - Sets an alias to a string.
 * @info: The parameter struct.
 * @str: string representing the alias in the format "alias_name=alias_value".
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	/* Find the position of the equal sign '=' in the alias string. */
	p = _strchr(str, '=');
	if (!p)
	{
		/* If there is no equal sign, return error (1). */
		return (1);
	}

	if (!*++p)
	{
		/* If there is no alias value after the equal sign, 
		unset the alias and return success (0). */
		return (unset_alias(info, str));
	}
		
	/* Unset any existing alias with the same name. */
	unset_alias(info, str);

	/* Add the new alias entry to the end of the alias list. */
	/* Return 0 on success, 1 on error. */
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node containing the alias string.
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		/* Find the position of the equal sign in the alias string. */
		p = _strchr(node->str, '=');
		/* Print the alias name part up to the equal sign. */
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\''); /* Print a single quote before the alias value. */
		_puts(p + 1);	/* Print the alias value part after the equal sign. */
		/* Print a new line character to complete the alias output. */
		_puts("'\n");
		return (0);		/* Return 0 on success. */
	}
	return (1); /* Return 1 on error (if the node is NULL). */
}

/**
 * my_alias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	/* If the alias command is used without any arguments, print all aliases. */
	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node); /* Print each alias entry in the alias list. */
			node = node->next;
		}
		return (0);
	}

	/* Loop through each argument provided to the alias command. */
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			/* Set alias using the provided argument. */
			set_alias(info, info->argv[i]);
		}
		else
		{
			/* Print alias by searching in the alias list. */
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}
