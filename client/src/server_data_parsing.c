/*
** EPITECH PROJECT, 2018
** server_data_parsing.c
** File description:
** function that handle parsing data from string to client readable
*/

#include "my_mmo.h"

int get_arg_nb(char *argv)
{
	int i = 0;
	int counter = 0;

	while (argv[i] != '\0') {
		if (argv[i] == '\n') {
			counter++;
			i++;
		} else {
			i++;
		}
	}
	return (counter);
}

char *set_string(char *argv, int old_i, int i)
{
	char *string = malloc((i - old_i + 1) * sizeof(char));
	int j = 0;

	for (int v = old_i; v < i; v++) {
		string[j] = argv[v];
		j++;
	}
	string[j] = 0;
	return (string);
}

char **set_args(char *argv, int nb)
{
	char **args = malloc((nb + 1) * sizeof(*args));
	int i = 0;
	int old_i = i;
	int counter = 0;

	while (argv[i] != 0) {
		if ((argv[i] == '\n')) {
			args[counter] = strdup(set_string(argv, old_i, i));
			counter++;
			i++;
			old_i = i;
		} else
			i++;
	}
	args[nb] = NULL;
	return (args);
}

char *parse_server_data_n(char *data, int a)
{
	char *string;
	int count = 0;
	int i = 0;
	int old_i = 0;

	while (data[i] != 0) {
		if (data[i] == ':' && count == (a)) {
			string = set_string(data, old_i, i);
			i++;
			old_i = i;
			break;
		} else if (data[i] == ':') {
			count++;
			old_i = i + 1;
			i++;
		} else {
			i++;
		}
	}
	return (string);
}