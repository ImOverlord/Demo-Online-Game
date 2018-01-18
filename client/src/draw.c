/*
** EPITECH PROJECT, 2018
** draw.c
** File description:
** online_draw.c
*/

#include "include.h"

int width = 800;
int height = 600;
int pixel_buffer = 4;

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

char *set(char *argv, int old_i, int i)
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
			args[counter] = strdup(set(argv, old_i, i));
			counter++;
			i++;
			old_i = i;
		} else
			i++;
	}
	args[nb] = NULL;
	return (args);
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
	sfHttp_setHost(http, "localhost:3000", 3000);
	request = sfHttpRequest_create();
	sfHttpRequest_setUri(request, "/map");
	sfHttpRequest_setMethod(request, sfHttpGet);
	response = sfHttp_sendRequest(http, request, timeout);
	in_highscore = strdup(sfHttpResponse_getBody(response));
	body = set_args(in_highscore, get_arg_nb(in_highscore));
	return (body);
}

char *parse_(char *data, int a)
{
	char *string;
	int count = 0;
	int i = 0;
	int old_i = 0;

	while (data[i] != 0) {
		if (data[i] == ':' && count == (a)) {
			string = set(data, old_i, i);
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

void draw_username(sfRenderWindow *window, char *username, int x, int y)
{
	sfText *text;
	sfFont *font;
	sfVector2f pos;

	font = sfFont_createFromFile("./ressources/arial.ttf");
	text = sfText_create();
	pos.x = x;
	pos.y = y;
	sfText_setFont(text, font);
	sfText_setString(text, username);
	sfText_setCharacterSize(text, 32);
	sfText_setColor(text, sfWhite);
	sfText_setPosition(text, pos);
	sfRenderWindow_drawText(window, text, NULL);
}

float get_rotation(int dir)
{
	if (dir == 1) {
		return (-90.0);
	}
	if (dir == 2) {
		return (90.0);
	}
	if (dir == 3) {
		return (180.0);
	}
	if (dir == 4) {
		return (0.0);
	}
	return (0.0);
}

void draw_player(sfRenderWindow *window, char *username, int x, int y, int dir)
{
	sfSprite *sprite;
	sfTexture *texture;
	float rotation;
	sfVector2f scale = {0.5, 0.5};
	sfVector2f pos = {x, y};
	sfVector2f origin = {313/2, 206/2};

	rotation = get_rotation(dir);
	texture = sfTexture_createFromFile("./ressources/player.png", NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setOrigin(sprite, origin);
	sfSprite_setScale(sprite, scale);
	sfSprite_setPosition(sprite, pos);
	sfSprite_setRotation(sprite, rotation);
	sfRenderWindow_drawSprite(window, sprite, NULL);
	sfTexture_destroy(texture);
	sfSprite_destroy(sprite);
	draw_username(window, username, x, y);
}

void draw_object(sfRenderWindow *window, int x, int y)
{
	sfSprite *sprite;
	sfTexture *texture;
	sfVector2f scale = {0.1, 0.1};
	sfVector2f pos = {x, y};

	texture = sfTexture_createFromFile("./ressources/player.png", NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setScale(sprite, scale);
	sfSprite_setPosition(sprite, pos);
	sfRenderWindow_drawSprite(window, sprite, NULL);
	sfTexture_destroy(texture);
	sfSprite_destroy(sprite);
}

void draw_from_server(sfRenderWindow *window, char **data, char *user)
{
	for (int i = 0; data[i] != NULL; i++) {
		int type = atoi(parse_(data[i], 0));
		char *username = parse_(data[i], 1);
		char *x1 = parse_(data[i], 2);
		char *y1 = parse_(data[i], 3);
		char *dir1 = parse_(data[i], 4);
		int x = atoi(x1);
		int y = atoi(y1);
		int dir = atoi(dir1);
		if (type == 1)
			draw_player(window, username, x, y, dir);
		if (type == 2)
			draw_object(window, x, y);
	}
}

int draw_(char *user)
{
	printf("Game Started\n");
	char **data = parse_data();
	char *me;
	sfVideoMode mode = {width, height, 32};
	sfRenderWindow* window;
	sfEvent event;

	window = sfRenderWindow_create(mode, user, sfResize | sfClose, NULL);
	while (sfRenderWindow_isOpen(window)) {
		data = parse_data();
		me = get_my(user);
		if (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed) {
				player_disconnect(user);
				sfRenderWindow_close(window);
				return (0);
			}
			if (sfKeyboard_isKeyPressed(sfKeyW)) {
				send_move(user, "1");
			}
			if (sfKeyboard_isKeyPressed(sfKeyS)) {
				send_move(user, "2");
			}
			if (sfKeyboard_isKeyPressed(sfKeyA)) {
				send_move(user, "3");
			}
			if (sfKeyboard_isKeyPressed(sfKeyD)) {
				send_move(user, "4");
			}
			if (sfKeyboard_isKeyPressed(sfKeySpace)) {
				player_shoot(me);
			}
		}
		sfRenderWindow_clear(window, sfBlack);
		draw_from_server(window, data, user);
		sfRenderWindow_display(window);
	}
	sfRenderWindow_destroy(window);
	return (1);
}