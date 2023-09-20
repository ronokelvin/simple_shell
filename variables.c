#include "shell.h"

/**
 * is_chain - Test if the current character in the buffer is a chain delimiter.
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in the buffer.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	/* Check if the current character and the next character
	 * form a CMD_OR (||) 
	 */
	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		/* Set the current position to NULL character to end the command */
		buf[j] = 0;
		j++; /* Increment j to skip the second '|' character */
		info->cmd_buf_type = CMD_OR; /* Set the command chain type to CMD_OR */
	}
	/* Check if the current character and the next character 
	* form a CMD_AND (&&) 
	*/
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		/* Set the current position to NULL character to end the command */
		buf[j] = 0;
		j++;/* Increment j to skip the second '&' character */
		/* Set the command chain type to CMD_AND */
		info->cmd_buf_type = CMD_AND;
	}
	/* Check if the current character is a semicolon ';'(end of this command)*/
	else if (buf[j] == ';')
	{
		/* Replace semicolon with null character to end the command */
		buf[j] = 0;
		/* Set the command chain type to CMD_CHAIN */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;		/* Update the pointer to the current position in the buffer */
	return (1); /* Return 1 to indicate that a chain delimiter was found */
}

/**
 * check_chain - Checks if we should continue chaining based on the last status
 * @info: Pointer to the parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in the buffer.
 * @i: Starting position in the buffer.
 * @len: Length of the buffer.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	/* Check if the command chain type is CMD_AND */
	if (info->cmd_buf_type == CMD_AND)
	{
		/* If the last command's exit status is non-zero (failed), break the chain */
		if (info->status)
		{
			buf[i] = 0; /* Set the current position to NULL character to end the chain */
			j = len;	/* Set j to len to stop further processing in the buffer */
		}
	}

	/* Check if the command chain type is CMD_OR */
	if (info->cmd_buf_type == CMD_OR)
	{
		/* If the last command's exit status is zero (successful),
		* break the chain 
		*/
		if (!info->status)
		{
			buf[i] = 0; /* Set the current position to NULL character to end the chain */
			j = len;	/* Set j to len to stop further processing in the buffer */
		}
	}

	*p = j; /* Update the pointer to the current position in the buffer */
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	/* Iterate through the first 10 arguments in the tokenized string */
	for (i = 0; i < 10; i++)
	{
		/* Find an alias that matches the first argument in info->alias list */
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0); /* Return 0 if no matching alias found */

		/* Free the original command and replace it with the alias value */
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0); /* Return 0 if invalid alias format found */

		p = _strdup(p + 1); /* Extract the alias value and duplicate it */
		if (!p)
			return (0); /* Return 0 if memory allocation for the alias value failed */

		info->argv[0] = p; /* Replace the original command with the alias value */
	}

	return (1); /* Return 1 to indicate successful replacement of alias */
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	/* Iterate through the tokenized string in info->argv */
	for (i = 0; info->argv[i]; i++)
	{
		/* Check if the token starts with '$' (variable symbol) */
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue; /* Skip if not a variable */

		/* Check for specific variables and perform replacements */

		/* If the token is "$?", replace it with the status value */
		if (!my_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, 0)));
			continue;
		}

		/* If the token is "$$", replace it with the process ID */
		if (!my_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		/* If the token is an environment variable (e.g., "$PATH"),
		 * look for the corresponding variable in info->env list
		 * and replace it with its value.
		 */
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
						   _strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		/* If the token is a single "$" (no variable name),
		 * replace it with an empty string.
		 */
		replace_string(&info->argv[i], _strdup(""));
	}

	return (0);
}

/**
 * replace_string - Replaces a string with a new string.
 * @old: Pointer to the address of the old string.
 * @new: Pointer to the new string.
 *
 * Return: 1 if the replacement is successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old); /* Free the memory occupied by the old string */
	*old = new; /* Assign the address of the new string to the old pointer */
	return (1); /* Return 1 to indicate successful replacement */
}
