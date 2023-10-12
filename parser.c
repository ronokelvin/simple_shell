#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct (unused in this function).
 * @path: Path to the file to be checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st; /* Structure to hold file information */

	(void)info; /* Avoid unused parameter warning */

	/* Check if 'path' is NULL or stat fails to obtain file information */
	if (!path || stat(path, &st))
		return (0);

	/* Check if the file is a regular file (not a directory or special file) */
	if (st.st_mode & S_IFREG)
	{
		/* Return 1 to indicate that the file is an executable command */
		return (1);
	}

	/* Return 0 to indicate that the file is not an executable command */
	return (0);
}

/**
 * duplicate_chars - Duplicates characters from a string.
 * @pathstr: The source string.
 * @start: Starting index from where to copy characters.
 * @stop: Stopping index (exclusive) indicating the end of copying.
 *
 * Return: Pointer to the new buffer containing the duplicated characters.
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024]; /* Static buffer to store the duplicated characters */
	int i = 0, k = 0;

	/* Iterate through the specified range [start, stop) */
	for (k = 0, i = start; i < stop; i++)
	{
		/* Copy non-delimiter characters from pathstr to buf */
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}

	buf[k] = 0;	  /* Null-terminate the buffer to create a valid C-string */
	return (buf);
	/* Pointer return to buffer containing the duplicated characters */
}

/**
 * find_path - Finds the specified command in the PATH string.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string containing directories separated by ':'.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	/* if cmd starts with "./" and valid then current directory */
	if ((my_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		/* If the end of pathstr or a ':' is reached */
		if (!pathstr[i] || pathstr[i] == ':')
		{
			/* Extract a portion of the pathstr to form a directory path */
			path = duplicate_chars(pathstr, curr_pos, i);

			/* If the path is empty, concatenate the cmd directly */
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/"); /* Concatenate '/' to form a full path */
				_strcat(path, cmd); /* Concatenate the cmd to the path */
			}

			/* Check if the command exists in the path */
			if (is_cmd(info, path))
				return (path);

			/* If the end of pathstr is reached, break out of the loop */
			if (!pathstr[i])
				break;

			curr_pos = i; /* Update the current position to start the next iteration */
		}
		i++; /* Move to the next character in pathstr */
	}

	return (NULL);
	/* Return NULL if the command was not found in any path directory */
}
