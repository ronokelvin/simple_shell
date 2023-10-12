#include "shell.h"

/**
 * hsh - the main main shell loop.
 * @info: info struct.
 * @av: the argument vector from the main function.
 *
 * Return: returns 0 on success, and 1/error code on error.
 */
int hsh(info_t *info, char **av)
{
	ssize_t k = 0;
	int builtin_ret = 0;

	/* Loop */
	while (k != -1 && builtin_ret != -2)
	{
		/* Info struct cleared for new command*/
		clear_info(info);

		/* Display prompt if in interactive mode */
		if (interactive_mode(info))
			_puts("$ ");

		/* Reads input char by char */
		_inputchar(BUF_FLUSH);
		k = get_input(info);

		if (k != -1)
		{
			/* info struct set with parsed command*/
			set_info(info, av);

			/* Check if command is builtin*/
			builtin_ret = find_builtin(info);

			/* Else find and execute command */
			if (builtin_ret == -1)
				find_command(info);
		}
		/* If EOF print newline and exit loop*/
		else if (interactive_mode(info))
			_putchar('\n');

		/* Memory allocated is freed*/
		free_info(info, 0);
	}

	/* Write command history to file before exiting */
	write_history(info);

	/* Free remaining memory and exit */
	free_info(info, 1);

	/* If not in interactive mode and there was an error,exit with status */
	if (!interactive_mode(info) && info->status)
		exit(info->status);

	/* If a built-in function returns -2,exit with the specified error number */
	if (builtin_ret == -2)
	{
		/* If no specific error number is provided,exit with the status */
		if (info->err_num == -1)
			exit(info->status);
		/* Exit with the specified error number */
		exit(info->err_num);
	}

	/* Return the result of the last built-in function */
	return (builtin_ret);
}

/**
 * find_builtin - function to find a builtin command.
 * @info: info struct.
 *
 * Return:  returns 0 if builtin executed successfully,
 *			returns 1 if builtin found but not successful,
 *			returns -1 if builtin not found,
 *			returns -2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{"help", my_help},
		{NULL, NULL}};

	/* Loop through the builtin table to find a match */
	for (i = 0; builtintbl[i].type; i++)
		if (my_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			/* Call the appropriate builtin function */
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH.
 * @info: info struct.
 *
 * Return: returns nothing.
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, num_args;

	info->path = info->argv[0];

	/* Increment line count if linecount_flag is set */
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	/* Count non-delimiter arguments */
	for (i = 0, num_args = 0; info->arg[i]; i++)
	{
		if (!is_delimiter(info->arg[i], " \t\n"))
			num_args++;
	}

	/* If there are no arguments, return from the function */
	if (!num_args)
		return;

	/* Find the command in the PATH environment variable */
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		/* If the command is found in the PATH, execute it using fork_command */
		info->path = path;
		fork_command(info);
	}
	else
	{
		/* If the command is not found in the PATH, check other conditions */
		if ((interactive_mode(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			/* Execute the command using fork_command */
			fork_command(info);
		}
		else if (*(info->arg) != '\n')
		{
			/* If none of the conditions are met and the command is not a newline,set status to 127 and print an error message.*/
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
/**
 * fork_command - forks an exec thread to run command.
 * @info: info struct.
 *
 * Return: returns nothing.
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* --- Child process ---Attempt to execute the command using execve*/
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			/*If execve returns - 1, an error occurred during execution,`Free allocated memory in the info struct*/
			free_info(info, 1);
			/*Check the errno to determine the specific error*/
			if (errno == EACCES)
				exit(126); /*Permission denied*/
			exit(1);
		}
	}
	else
	{
		/* --- Parent process --- Wait for the child process to finish execution and retrieve its exit status*/
		wait(&(info->status));
		/* Check if the child process exited normally*/
		if (WIFEXITED(info->status))
		{
			/*Update the info status with the exit status of the child process*/
			info->status = WEXITSTATUS(info->status);
			/*If the child process returned 126, it means "Permission denied"*/
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
