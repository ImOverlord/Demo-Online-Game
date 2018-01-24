/*
** EPITECH PROJECT, 2018
** client.c
** File description:
** client connection script
*/

#include "my_mmo.h"

void show_help(void)
{
	printf("Online Test Game\n\n");
	printf("USAGE:\n");
	printf("No Args:\tLogin\n");
	printf("r:\t\tRegister an account\n");
	printf("-h:\t\tHelp\n\n");
	printf("DESCRIPTION\n");
	printf("Demo Game to show netwoking with CSFML\n");
	printf("Created By ImOverlord\n");
	printf("https://github.com/ImOverlord/\n");
}

int main(int ac, char **argv)
{
	char *user;

	printf("%d\n", sfKeyA);

	if (ac == 2 && strcmp(argv[1], "r") == 0) {
		user = register_user();
		draw_(user);
	} else if (ac == 2 && strcmp(argv[1], "-h") == 0) {
		show_help();
	} else {
		user = get_user();
		draw_(user);
	}
	return (0);
}