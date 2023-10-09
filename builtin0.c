#include "shell.h"

/**
 * my_exit - Exits the shell.
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Exits with a given exit status:
 *         - (-1) if info->argv[0] != "exit"
 *         - (-2) if info->argv[1] is valid number and used as the exit status
 *         - (1) if info->argv[1] is not a valid number or not provided
 */
int my_exit(info_t *info)
{
	int exitcheck;

	/* Check if there is an exit argument provided in info->argv[1]. */
	if (info->argv[1])
	{
		exitcheck = _erroratoi(info->argv[1]);
		/*Check if _erroratoi returned -1, indicating an invalid number format.*/
		if (exitcheck == -1)
		{
			/* Set the status to 2 and print an error message indicating an illegal number format. */
			info->status = 2;
			print_error(info, "Illegal number: ");
			_inputs(info->argv[1]);
			_inputchar('\n');
			return (1); /* Return 1 to indicate an error. */
		}

		/* Store the valid exit status in the info->err_num variable. */
		info->err_num = _erroratoi(info->argv[1]);

		return (-2); /* Return -2 to indicate that the exit status should be used. */
	}

	/* If no exit argument is provided, set info->err_num to -1 and return -2 to indicate exit should be used. */
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0.
 */
int my_cd(info_t *info)
{
	/* Variables to store directory information and buffer for getcwd. */
	char *s, *dir, buffer[1024];
	int chdir_ret;				 /* Return value of the chdir function. */

	/* Get the current working directory and store it in 's'. */
	s = getcwd(buffer, 1024);

	/* Check if getcwd failed. If so, print an error message. */
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	/* Check if no directory argument is provided. */
	if (!info->argv[1])
	{
		/* Get the home directory using the '_getenv' function. */
		dir = _getenv(info, "HOME=");

		/* If the home directory is not set, use the 'PWD' environment variable as the default directory. */
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	/* Check if the argument is a hyphen ('-'), representing the previous working directory. */
	else if (my_strcmp(info->argv[1], "-") == 0)
	{
		/* Check if the 'OLDPWD' environment variable is not set. */
		if (!_getenv(info, "OLDPWD="))
		{
			/* Print the current working directory and return. */
			_puts(s);
			_putchar('\n');
			return (1);
		}

		/* Print the 'OLDPWD' environment variable and change to that directory. */
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	/* If the argument is a directory path, change to that directory. */
	else
		chdir_ret = chdir(info->argv[1]);

	/* Check if the chdir operation was unsuccessful. */
	if (chdir_ret == -1)
	{
		/* Print an error message indicating that the 'cd' operation failed for the specified directory. */
		print_error(info, "can't cd to ");
		_inputs(info->argv[1]);
		_inputchar('\n');
	}
	else
	{
		/* Update the 'OLDPWD' and 'PWD' environment variables with the new and old working directories, respectively. */
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	/* Return 0 to indicate successful execution of the 'my_cd' function. */
	return (0);
}

/**
 * my_help - Prints a help message for the shell.
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0.
 */
int my_help(info_t *info)
{
	char **arg_array; /* Array of strings representing the command arguments. */

	/* Retrieve the array of command arguments from the 'info' struct. */
	arg_array = info->argv;

	/* Print a help message indicating that the function is not yet implemented. */
	_puts("help call works. Function not yet implemented \n");

	if (0)
		_puts(*arg_array); /* temp att_unused workaround */

	/* Return 0 to indicate successful execution of the 'my_help' function. */
	return (0);
}
