/*
** EPITECH PROJECT, 2018
** client_http_disconnect.c
** File description:
** function for player disconnection
*/

#include "my_mmo.h"

void player_disconnect(char *user)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfTime timeout = sfSeconds(1);
	char *packet = concat("username=", user);

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/disconnect");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	sfHttp_sendRequest(http, request, timeout);
	printf("Disconnected\n");
}