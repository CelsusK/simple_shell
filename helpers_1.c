#include "shell.h"

/**
 *_strcmp - It compare two strings
 *@first: The first string to be compared
 *@second: The second string to be compared
 *
 * Return: The difference of the two strings
 */

int _strcmp(char *first, char *second)
{
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}
	return (first[i] - second[i]);
}

/**
 *_strcat - links two strings
 *@destination: The string to be linked to
 *@source:  string to link
 *
 * Return: The address of the new string
 */

char *_strcat(char *destination, char *source)
{
	char *new_string =  NULL;
	int len_dest = _strlen(destination);
	int len_source = _strlen(source);

	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	_strcpy(destination, new_string);
	_strcpy(source, new_string + len_dest);
	new_string[len_dest + len_source] = '\0';
	return (new_string);
}

/**
 *_strspn - It gets the length of a prefix substring
 *@str1: The string to be searched
 *@str2: The string to be used
 *
 *Return: Thenumber of bytes in the initial segment of 5 which are part of accepttt
 */

int _strspn(char *str1, char *str2)
{
	int i = 0;
	int match = 0;

	while (str1[i] != '\0')
	{
		if (_strchr(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}

/**
 *_strcspn - checks segment of str1 which consists of characters not in str2
 *@str1: The string to be searched
 *@str2: The string to be used
 *
 *Return: index at which a char in str1 existts in str2
 */


int _strcspn(char *str1, char *str2)
{
	int len = 0, i;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (_strchr(str2, str1[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 *_strchr - It locates a char in a string
 *@s: The string to be searched
 *@c: The char to be checked
 *
 *Return: The pointer to the first occurence of c in s
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
