#include "shell.h"

/**
 * input_buf - Buffers chained commands for processing.
 * @info: Pointer to the parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the len variable.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/* Free any previous buffer */
		free(*buf);
		*buf = NULL;

		/* Set signal handler for SIGINT (Ctrl-C) */
		signal(SIGINT, sigint_handler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			/* Check if this is a command chain */
			/* if (_strchr(*buf, ';')) */
			{
				*len = r;			 /* Set the length of the buffer */
				info->cmd_buf = buf; /* Store the address of the buffer */
			}
		}
	}
	return (r); /* Return the number of bytes read */
}

/**
 * get_input - Gets a line of input without the newline character.
 * @info: Pointer to the parameter struct.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	/* Flush the buffer */
	_putchar(BUF_FLUSH);

	/* Read data into the buffer */
	r = input_buf(info, &buf, &len);

	/* If end of file (EOF) is reached, return -1 */
	if (r == -1)
		return (-1);

	/* If there are commands left in the chain buffer */
	if (len)
	{
		j = i;/* Initialize new iterator to the current buf position */
		p = buf + i; /* Get pointer for return */

		/* Check for command chaining and update the iterator accordingly */
		check_chain(info, buf, &j, i, len);

		/* Iterate to find the next semicolon or the end of the buffer */
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;	  /* Increment past the nulled semicolon */
		if (i >= len) /* Reached the end of the buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;/* Pass back the pointer to the current command position */
		return (my_strlen(p)); /* Return the length of the current command */
	}

	/* Not a command chain, pass back the buffer from _getline() */
	*buf_p = buf;
	return (r); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Reads a buffer from the input file descriptor.
 * @info: Pointer to the parameter struct.
 * @buf: Buffer to store the read data.
 * @i: Pointer to the size of the buffer.
 *
 * Return: The number of bytes read from the input file descriptor.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	/* If buffer is not empty, no need to read further */
	if (*i)
		return (0);

	/* Read data from the input file descriptor into the buffer */
	r = read(info->readfd, buf, READ_BUF_SIZE);

	/* If read is successful, update the size of the buffer */
	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Pointer to the parameter struct.
 * @ptr: Address of a pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: The number of characters read from the input stream.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		str = *length;

	/* Reset index and length if buffer is exhausted */
	if (i == len)
		i = len = 0;

	/* Read data from input buffer */
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	/* Find the position of the newline character in the buffer */
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;

	/* Reallocate memory for the new_p buffer */
	new_p = _realloc(p, str, str ? str + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	/* Copy data from the buffer to the new_p buffer */
	if (str)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	str += k - i;
	i = k;
	p = new_p;

	/* Update length if a pointer to length is provided */
	if (length)
		*length = str;
	*ptr = p;
	return (str);
}

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl-C).
 * @sig_num: The signal number (unused).
 *
 * Return: void.
 */
void sigint_handler(__attribute__((unused)) int sig_num)
{
	/* Print a new line and the shell prompt after receiving SIGINT */
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
