#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	/* Traverse the linked list and count the number of nodes */
	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Returns an array of strings from the list's str element.
 * @head: Pointer to the first node of the list.
 *
 * Return: Array of strings or NULL on failure.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	/* Allocate memory for the array of strings */
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	/* Iterate through the linked list and copy each node's str to the array */
	for (i = 0; node; node = node->next, i++)
	{
		/* Allocate memory for each string and copy the node's str into it */
		str = malloc(my_strlen(node->str) + 1);
		if (!str)
		{
			/* Free previously allocated strings in case of failure */
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		/* Copy the string from the node's str to the allocated memory */
		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	/* Add NULL as the last element of the array to mark the end */
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	/* Traverse the linked list and print each element */
	while (h)
	{
		/* Print the node number */
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');

		/* Print the string (str) of the node or "(nil)" if str is NULL */
		_puts(h->str ? h->str : "(nil)");

		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - Returns the node whose string starts with the prefix.
 * @node: Pointer to the head of the list.
 * @prefix: String to match as the prefix.
 * @c: The next character after the prefix to match.
 *
 * Return: Pointer to the matching node or NULL if no match.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	/** Linked list traversed finding node with matching prefix next character*/
	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in the linked list.
 * @head: Pointer to the head of the list.
 * @node: Pointer to the node whose index is to be found.
 *
 * Return: Index of the node or -1 if the node is not found in the list.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	/* Traverse the linked list and find the index of the node */
	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
