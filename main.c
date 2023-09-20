#include "shell.h"

/**
 * main - the entry point
 * @ac: the number of items in av (command-line arguments count)
 * @av: array of strings (command-line arguments)
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	/*Create and initialize an info_t struct instance*/
	info_t info[] = {INFO_INIT};
	int fd = 2; /*File descriptor*/

	/*Inline assembly to update the file descriptor 'fd'*/
	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	/*Check if a script file is provided as an argument*/
	if (ac == 2)
	{
		/*Open the provided script file in read-only mode*/
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			/*Handle errors when opening the script file*/
			if (errno == EACCES)
				exit(126); /*Permission denied*/
			if (errno == ENOENT)
			{
				_inputs(av[0]);
				_inputs(": 0: Can't open ");
				_inputs(av[1]);
				_inputchar('\n');
				_inputchar(BUF_FLUSH);
				exit(127); /*Command not found*/
			}
			return (EXIT_FAILURE);
		}
		/*Set the read file descriptor to the opened file*/
		info->readfd = fd;
	}

	/*Display the environment list*/
	display_env_list(info);
	/*Read the command history*/
	read_history(info);
	/*Start the shell (read and execute commands)*/
	hsh(info, av);
	/*Return success*/
	return (EXIT_SUCCESS);
}
