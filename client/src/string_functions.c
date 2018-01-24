/*
** EPITECH PROJECT, 2018
** string_functions.c
** File description:
** function to handle strings.c
*/

#include "my_mmo.h"

char *concat(char const *str1, char const *str2)
{
	char *string = malloc( (strlen(str1) + strlen(str2) + 1) * sizeof(char));
	int i = 0;

	if (string == NULL)
		return (NULL);
	for (int j = 0; str1[j] != 0; j++) {
		string[i] = str1[j];
		i++;
	}
	for (int j = 0; str2[j] != 0; j++) {
		string[i] = str2[j];
		i++;
	}
	string[i] = 0;
	return (string);
}