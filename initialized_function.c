#include "shell.h"

/**
 * initializer - executes everything
 * @current_command: tries to check current token
 * @type_command: the parse token
 *
 * Return: void function
 */

void initializer(char **current_command, int type_command)
{
	PID_t pid;

	if (type_command == external_command || type_command == PATH_COMMAND)
	{
		PID = fork();
		if (pid == 0)
			execute_command(current_command, type_command);
		else
		{
			waitpid(pid, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(current_command, type_command);
}
