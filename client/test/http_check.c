/*
** EPITECH PROJECT, 2018
** http_check.c
** File description:
** function to test server connection
*/

#include "my_mmo.h"
#include <criterion/criterion.h>

int check_server_up(void)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfHttpResponse *response;
	sfTime timeout = sfSeconds(1);
	char *packet = "NULL";

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/hello");
	sfHttpRequest_setMethod(request, sfHttpGet);
	sfHttpRequest_setBody(request, packet);
	response = sfHttp_sendRequest(http, request, timeout);
	if (sfHttpResponse_getStatus(response) == sfHttpOk) {
		printf("Success\n");
		return (0);
	} else {
		printf("Error: %d\n", sfHttpResponse_getStatus(response));
		return (-1);
	}
	return (84);
}


Test(check_server, check_server_is_up)
{
	cr_expect(check_server_up() == 0, "Server Is Unreachable");
}