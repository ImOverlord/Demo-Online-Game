/*
** EPITECH PROJECT, 2018
** client.c
** File description:
** client connection script
*/

#include "include.h"

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
	sfHttp_setHost(http, "localhost:3000", 3000);
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
	sfHttp_setHost(http, "localhost:3000", 3000);
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

void player_disconnect(char *user)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfTime timeout = sfSeconds(1);
	char *packet = concat("username=", user);

	http = sfHttp_create();
	sfHttp_setHost(http, "localhost:3000", 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/disconnect");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	sfHttp_sendRequest(http, request, timeout);
	printf("Disconnected\n");
}

void send_move(char *user, char *move)
{
	sfHttp *http;
	sfHttpRequest *request;
	sfTime timeout = sfSeconds(1);
	char *user_packet = concat("username=", user);
	char *move_packet = concat("&move=", move);
	char *packet = concat(user_packet, move_packet);

	http = sfHttp_create();
	sfHttp_setHost(http, "localhost:3000", 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/move");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	sfHttp_sendRequest(http, request, timeout);
}

void player_shoot(char *me)
{
	printf("%s", me);
	sfHttp *http;
	sfHttpRequest *request;
	sfTime timeout = sfSeconds(1);
	char *username = parse_(me, 1);
	char *x1 = parse_(me, 2);
	char *y1 = parse_(me, 3);
	char *dir1 = parse_(me, 4);
	char *username_packet = concat("username=", username);
	char *x_packet = concat("&x=", x1);
	char *y_packet = concat("&y=", y1);
	char *dir_packet = concat("&direction=", dir1);
	char *packet = concat(username_packet, x_packet);
	packet = concat(packet, y_packet);
	packet = concat(packet, dir_packet);

	http = sfHttp_create();
	sfHttp_setHost(http, "localhost:3000", 3000);
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
	sfHttp_setHost(http, "localhost:3000", 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/my");
	sfHttpRequest_setMethod(request, sfHttpPost);
	sfHttpRequest_setBody(request, packet);
	response = sfHttp_sendRequest(http, request, timeout);
	in_highscore = strdup(sfHttpResponse_getBody(response));
	return (in_highscore);
}

int main(int ac, char **argv)
{
	char *user;

	if (ac == 2 && strcmp(argv[1], "1") == 0) {
		user = register_user();
		draw_(user);
	} else if (ac == 2 && strcmp(argv[1], "0") == 0) {
		user = get_user();
		draw_(user);
	} else {
		user = get_user();
		draw_(user);
	}
}