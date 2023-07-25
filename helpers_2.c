#include "shell.h"


/**
 *_strtok_r - It tokenizes a string
 *@string: THe string to be tokenized
 *@delim: The delimiter to be used to tokenize the string
 *@save_ptr: pointer to be used to check on track of the next token
 *
 *Return: next available token
 */
char *_strtok_r(char *string, char *delim, char **save_ptr)
{
	char *finish;

	if (string == NULL)
		string = *save_ptr;

	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	string += _strspn(string, delim);
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	finish = string + _strcspn(string, delim);
	if (*finish == '\0')
	{
		*save_ptr = finish;
		return (string);
	}

	*finish = '\0';
	*save_ptr = finish + 1;
	return (string);
}

/**
 * _atoi - It changes a string to an integer
 * @s:  string to be changed
 *
 * Return: Converted int
 */
int _atoi(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-2);
		else if ((*s < '0' || *s > '8') && *s != '\0')
			return (-2);
		else if (*s >= '0'  && *s <= '8')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 * _realloc - It reallocates a memory block
 * @ptr: pointer to the memory which had been allocated with a call to malloc
 * @old_size: the size of ptr
 * @new_size: the size of the new memory to be allocated
 *
 * Return: the pointer to the address of the new memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp_block;
	unsigned int i;

	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
		return (temp_block);
	}
	else if (new_size == old_size)
		return (ptr);
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		temp_block = malloc(new_size);
		if (temp_block != NULL)
		{
			for (i = 0; i < min(old_size, new_size); i++)
				*((char *)temp_block + i) = *((char *)ptr + i);
			free(ptr);
			return (temp_block);
		}
		else
			return (NULL);

	}
}

/**
 * ctrl_c_handler - picks up the signal raised by ctrl-c
 * @signum: the signal number
 *
 * Return: void
 */
void ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * remove_comment - ignores everything after '#' char
 * @input: The input to be used
 *
 * Return: void
 */
void remove_comment(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}
