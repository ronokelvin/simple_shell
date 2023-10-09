# Simple Shell in C#
We created a simple shell as part of our Alx journey in learning software engineering.
# List of allowed functions and system calls in the project include
	* access (man 2 access)
	* chdir (man 2 chdir)
	* close (man 2 close)
	* closedir (man 3 closedir)
	* execve (man 2 execve)
	* exit (man 3 exit)
	* _exit (man 2 _exit)
	* fflush (man 3 fflush)
	* fork (man 2 fork)
	* free (man 3 free)
	* getcwd (man 3 getcwd)
	* getline (man 3 getline)
	* getpid (man 2 getpid)
	* isatty (man 3 isatty)
	* kill (man 2 kill)
	* malloc (man 3 malloc)
	* open (man 2 open)
	* opendir (man 3 opendir)
	* perror (man 3 perror)
	* read (man 2 read)
	* readdir (man 3 readdir)
	* signal (man 2 signal)
	* stat (__xstat) (man 2 stat)
	* lstat (__lxstat) (man 2 lstat)
	* fstat (__fxstat) (man 2 fstat)
	* strtok (man 3 strtok)
	* wait (man 2 wait)
	* waitpid (man 2 waitpid)
	* wait3 (man 2 wait3)
	* wait4 (man 2 wait4)
	* write (man 2 write)
# Our shell was compiled using:
	*gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
# From the above function we were supposed to create a simple shell that can:
* Display a pompt and wait for user to type a command. A command line always ending with a new line.
* The prompt is displayed again each time a command has been executed.
* The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
* You have to handle the "end-of-file"
* Handle command lines with arguments.(Simple shell 0.1 +)
* Handle the PATH (simple shell 0.2+)
* fork must not be called if the command doesn't exist.(simple shell 0.2+)
* Implement the exit built-in, that exits the shell
* Usage: exit
* You don't have to handle any arguments to the built-in exit(simple shell 0.3+)
* Implement the env built-in, that prints the current environment.(simple shell 0.4 +)


