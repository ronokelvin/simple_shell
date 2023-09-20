#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	/* Check if 'info->environ' is NULL or the environment has been modified */
	if (!info->environ || info->env_changed)
	{
		/* Convert linked list to string array */
		info->environ = list_to_strings(info->env);
		/* Reset the environment change flag */
		info->env_changed = 0;
	}

	/* Return the string array containing the environment variables */
	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable from the linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string representing the environment variable to remove.
 *
 *
 * Return:
 * 1 if the environment variable was successfully deleted,
 * 0 if the variable was not found or if the linked list is empty.
 */
int _unsetenv(info_t *info, char *var)
{
	/* Pointer to the head of the environment variable linked list */
	list_t *node = info->env;
	/* Index to keep track of the position of the current node */
	size_t i = 0;
	/* Pointer used for string comparison */
	char *p;

	/** If the linked list is empty or the variable string is empty,
	 * 		return 0 indicating failure */
	if (!node || !var)
		return (0);

	/* Iterate through the linked list to search for the environment variable */
	while (node)
	{
		p = starts_with(node->str, var);
		/* If the variable is found, returns the pointer after the prefix */
		if (p && *p == '=')
		{
			/* Delete the node at index i */
			info->env_changed = delete_node_at_index(&(info->env), i);
			/** Reset the index to 0 after deleting the node
			 * 	to start from the beginning */
			i = 0;
			/* Reset the node pointer to the new head of the linked list */
			node = info->env;
			/* Continue searching for other occurrences of the variable */
			continue;
		}
		/* Move to the next node in the linked list */
		node = node->next;
		/* Increment the index for the next iteration */
		i++;
	}
	/** Return 1 if the environment variable was found and deleted,
	 * otherwise return 0 */
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	/* Create a buffer to store "var=value" string */
	buf = malloc(my_strlen(var) + my_strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	/* Search for the variable in the environment list */
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
