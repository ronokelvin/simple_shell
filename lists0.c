#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the new node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly added node, or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	/* Check if head pointer is NULL */
	if (!head)
		return (NULL);

	/* Allocate memory for the new node */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	/* Initialize the new node's fields to 0 */
	_memset((void *)new_head, 0, sizeof(list_t));

	/* Set the node index */
	new_head->num = num;

	/* Duplicate the input string and assign it to the new node's 'str' field */
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	/* Set the 'next' pointer of the new node to the current head node */
	new_head->next = *head;

	/* Update the head pointer to point to the new node */
	*head = new_head;

	/* Return a pointer to the newly added node */
	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the new node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly added node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	/* Check if head pointer is NULL */
	if (!head)
		return (NULL);

	/* Set the node pointer to the current head node */
	node = *head;

	/* Allocate memory for the new node */
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	/* Initialize the new node's fields to 0 */
	_memset((void *)new_node, 0, sizeof(list_t));

	/* Set the node index */
	new_node->num = num;

	/* Duplicate the input string and assign it to the new node's 'str' field */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	/* If the list is not empty, traverse to the end and add the new node there */
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	/* Return a pointer to the newly added node */
	return (new_node);
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	/* Traverse the list while the node pointer 'h' is not NULL */
	while (h)
	{
		/* Print the 'str' element of the current node, or "(nil)" if it's NULL */
		_puts(h->str ? h->str : "(nil)");

		/* Print a newline character after each string */
		_puts("\n");

		/* Move to the next node */
		h = h->next;

		/* Increment the counter for the size of the list */
		i++;
	}

	/* Return the size of the list */
	return (i);
}

/**
 * delete_node_at_index - Deletes the node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	/* Check if the head or the linked list is NULL */
	if (!head || !*head)
		return (0);

	/* If the index is 0, delete the first node */
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	/* Traverse the linked list to find the node at the given index */
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	/* If the index is out of range, return failure */
	return (0);
}

/**
 * free_list - Frees all nodes of a linked list.
 * @head_ptr: Address of pointer to head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	/* Check if the head or the linked list is NULL */
	if (!head_ptr || !*head_ptr)
		return;

	/* Store the head of the linked list in a temporary variable */
	head = *head_ptr;
	node = head;

	/* Traverse the linked list to free each node */
	while (node)
	{
		/* Store the next node before freeing the current node */
		next_node = node->next;
		/* Free the memory allocated for the string (str) */
		free(node->str);
		/* Free the current node */
		free(node);
		/* Move to the next node */
		node = next_node;
	}

	/* Update the head pointer to point to NULL (empty list) */
	*head_ptr = NULL;
}
