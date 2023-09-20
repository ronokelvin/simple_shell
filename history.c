#include "shell.h"

/**
 * get_history_file - Gets the history file path.
 * @info: Pointer to the parameter struct.
 *
 * Return: Returns the allocated string containing the history file path,
 *         or NULL if an error occurs or HOME environment variable is not set.
 */
char *get_history_file(info_t *info)
{
	char *buf, *directory;

	/* Get the value of the HOME environment variable */
	directory = _getenv(info, "HOME=");

	/* Check if HOME environment variable is not set */
	if (!directory)
		return (NULL);

	/* Allocate memory for the buffer to hold the history file path */
	buf = malloc(sizeof(char) * (my_strlen(directory) + my_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	/* Clear the buffer by setting the first element to null terminator */
	buf[0] = '\0';

	/* Copy the HOME directory path to the buffer */
	_strcpy(buf, directory);

	/* Concatenate a '/' to the buffer */
	_strcat(buf, "/");

	/* Concatenate the HIST_FILE to the buffer */
	_strcat(buf, HIST_FILE);

	/* Return the buffer containing the history file path */
	return (buf);
}

/**
 * write_history - Creates a file or appends to
 * 					an existing file with command history.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 on success, else -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	/* Get the history file path */
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		/* Return -1 if history file path is not available */
		return (-1);

	/* Open or create the history file */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		/* Return -1 if unable to open or create the history file */
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		/* Write the history command to the history file */
		_putsfd(node->str, fd);
		/* Append a newline after each command */
		_putfd('\n', fd);
	}
	/* Flush the buffer to ensure data is written to the file */
	_putfd(BUF_FLUSH, fd);
	close(fd); /* Close the file */

	return (1); /* Return 1 on successful write */
}

/**
 * read_history - Reads history from a file and builds a history list.
 * @info: Pointer to the parameter struct.
 *
 * Return: The number of history lines read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0); /* Return 0 if history file path is not available */

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0); /* Return 0 if unable to open the history file */

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		/* Return 0 if the history file is empty
		or contains only one character */
		return (0);

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0); /* Return 0 if memory allocation fails */

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0)
		/* Return 0 if there was an error reading the file */
		return (free(buf), 0);

	close(fd);

	/* Parse the read buffer and build the history list */
	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	/* If there's a partial line at the end, build it as well */
	if (last != i)
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	/* Remove history lines beyond HIST_MAX and renumber the list */
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);

	/* Return the number of history lines read */
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments. 
 * 			Used to maintain history.
 * @buf: The buffer containing the history command to add.
 * @linecount: The history linecount, histcount.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL; /* Create a pointer to a list node */

	/* If the history list is not empty,
	set the node pointer to the current head */
	if (info->history)
		node = info->history;

	/* Add a new node to the end of the history list
	with the provided command and linecount */
	add_node_end(&node, buf, linecount);

	/* If the history list was empty,
	update the head pointer to the newly added node */
	if (!info->history)
		info->history = node;

	return (0); /* Return 0 to indicate success */
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments. Used to maintain history.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	/* Traverse the history list and update the node numbers */
	while (node)
	{
		/*Assign the current value of 'i' to the 'num' field of the node
		and then increment 'i'*/
		node->num = i++;
		/*Move to the next node in the list*/
		node = node->next;
	}

	/* Update the histcount to the new value */
	return (info->histcount = i);
}
