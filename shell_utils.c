#include "shell.h"

/**
 * Auth: Cassian Kiragu 		 
 *
 * Description:
 * more functions for main.c
 */


/** parse_command - It determines the type of the command
 * @command: The command to be parsed
 *
 * Return: The constant representing the type of the command
 * Description -
 * 		 external_command (1) it represents commands like bin/ls
 *		 internal_command (2) it represents commands like exit,environ
 *		 path_command (3) It represents commands found in the path like ls
 *		 INVALID_command (-1) it represents INVALID commands
 */

int parse_command(char *command)
{
	int i;
	char *INTERNAL_COMMAND[] = {"environ", "exit", NULL};
	char *PATH = NULL;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (external_command);
	}
	for (i = 0; INTERNAL_COMMAND[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the path */
	path = check_path(command);
	if (PATH != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_command);
}

/**
 * execute_command - It executes a command based on type
 * @tokenized_command: The tokenized form of the command (ls -l == {ls, -l, NULL})
 * @command_type: THe type of the command
 *
 * Return: void
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == external_command)
	{
		if (execue(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_geten("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execue(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_geten("PWD"));
			exit(2);
		}
	}
	if (command_type == internal_command)
	{
		func = get_func(tokenized_command[0]);
		func(tokenized_command);
	}
	if (command_type == INVALID_command)
	{
		print(shell_name, STDERR_FILENO);
		print(":1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(":not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - It checks if a command is found in the path
 * @command: The command to be used
 *
 * Return: The path where the command isto be found in, NULL if not able to be found
 */
char *check_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _geten("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - It retrieves a function based on the command given and the mapping
 * @command:The string to check against the mapping
 *
 * Return: the pointer to the proper function, or null which is on fail
 */
void (*get_func(char *command))(char **)
{
	int i;
	function_map mapping[] = {
		{"environ", environ}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 * _geten - it gets the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return:  value of the variable as a string
 */
char *_geten(char *name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	for (my_environ = enviro; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = name;
		     *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}
