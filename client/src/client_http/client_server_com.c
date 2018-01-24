/*
** EPITECH PROJECT, 2018
** client_server_com.c
** File description:
** function that handle getting information from server for game
*/

#include "my_mmo.h"

void send_move(char *user, char *move)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfTime timeout = sfSeconds(1);
	char *user_packet = concat("username=", user);
	char *move_packet = concat("&move=", move);
	char *packet = concat(user_packet, move_packet);

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/move");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	sfHttp_sendRequest(http, request, timeout);
}

void player_shoot(char *me)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfTime timeout = sfSeconds(1);
	char *username = parse_server_data_n(me, 1);
	char *x1 = parse_server_data_n(me, 2);
	char *y1 = parse_server_data_n(me, 3);
	char *dir1 = parse_server_data_n(me, 4);
	char *username_packet = concat("username=", username);
	char *x_packet = concat("&x=", x1);
	char *y_packet = concat("&y=", y1);
	char *dir_packet = concat("&direction=", dir1);
	char *packet = concat(username_packet, x_packet);
	packet = concat(packet, y_packet);
	packet = concat(packet, dir_packet);

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/shoot");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	sfHttp_sendRequest(http, request, timeout);
}

char *get_my(char *user)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfHttpResponse *response;
	sfTime timeout = sfSeconds(1);
	char *in_highscore;
	char *packet = concat("username=", user);

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/my");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	response = sfHttp_sendRequest(http, request, timeout);
	in_highscore = strdup(sfHttpResponse_getBody(response));
	return (in_highscore);
}

char **parse_data(void)
{
	char **body;
	sfHttp *http;
	sfHttpRequest *request;
	sfHttpResponse *response;
	sfTime timeout = sfSeconds(1);
	char *in_highscore;

	http = sfHttp_create();
	sfHttp_setHost(http, server_ip, 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/map");
	sfHttpRequest_setMethod(request, sfHttpGet);
	response = sfHttp_sendRequest(http, request, timeout);
	in_highscore = strdup(sfHttpResponse_getBody(response));
	body = set_args(in_highscore, get_arg_nb(in_highscore));
	return (body);
}