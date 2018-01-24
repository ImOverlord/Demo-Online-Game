/*
** EPITECH PROJECT, 2018
** client_http_register.c
** File description:
** function to handle registering a new account
*/

#include "my_mmo.h"

int register_(char *user, char *password)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfHttpResponse *response;
	sfTime timeout = sfSeconds(1);
	char *in_highscore;
	char *user_packet = concat("username=", user);
	char *password_packet = concat("password=", password);
	char *packet = concat(concat(user_packet, "&"), password_packet);

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/register");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	response = sfHttp_sendRequest(http, request, timeout);
	in_highscore = strdup(sfHttpResponse_getBody(response));
	if (strcmp(in_highscore, "1") == 0) {
		return (0);
	} else {
		return (-1);
	}
}

char *register_user(void)
{
	char *user = malloc(20);
	char *password = malloc(20);
	int size;

	printf("Register: \n");
	write(1, "Username: ", 10);
	size = read(1, user, 19);
	user[size-1] = 0;
	write(1, "Password: ", 10);
	size = read(1, password, 19);
	password[size-1] = 0;

	if (register_(user, password) == -1) {
		printf("Registeration Failed\n");
		register_user();
	} else {
		printf("Registertation Successful\n");
		return (user);
	}
	return (NULL);
}