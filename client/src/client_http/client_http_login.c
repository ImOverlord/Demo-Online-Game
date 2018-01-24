/*
** EPITECH PROJECT, 2018
** http_client_login.c
** File description:
** function to manage player login
*/

#include "my_mmo.h"

int login(char *user, char *password)
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
	sfHttpRequest_setUri(request, "/login");
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

char *get_user(void)
{
	char *user = malloc(20);
	char *password = malloc(20);
	int size;

	printf("Login: \n");
	write(1, "Username: ", 10);
	size = read(1, user, 19);
	user[size-1] = 0;
	write(1, "Password: ", 10);
	size = read(1, password, 19);
	password[size-1] = 0;

	if (login(user, password) == -1) {
		printf("Login Failed\n");
		get_user();
	} else {
		printf("Login Successful\n");
		return (user);
	}
	return (NULL);
}