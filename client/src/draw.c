/*
** EPITECH PROJECT, 2018
** draw.c
** File description:
** online_draw.c
*/

#include "my_mmo.h"

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

void draw_map(sfRenderWindow *window)
{
	sfTexture *texture;
	sfSprite *sprite;
	sfVector2f scale = {10, 10};
	
	texture = sfTexture_createFromFile("./ressources/map1.png", NULL);
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setScale(sprite, scale);
	sfRenderWindow_drawSprite(window, sprite, NULL);
	sfTexture_destroy(texture);
	sfSprite_destroy(sprite);
}

void focus(sfRenderWindow *window, int x, int y)
{
	sfView *camera;
	sfVector2f center = {x, y};
	sfFloatRect cam = {0, 0, width, height};

	camera = sfView_createFromRect(cam);
	sfView_setCenter(camera, center);
	sfRenderWindow_setView(window, camera);
}

void draw_from_server(sfRenderWindow *window, char **data, char *user)
{
	draw_map(window);
	for (int i = 0; data[i] != NULL; i++) {
		int type = atoi(parse_server_data_n(data[i], 0));
		char *username = parse_server_data_n(data[i], 1);
		char *x1 = parse_server_data_n(data[i], 2);
		char *y1 = parse_server_data_n(data[i], 3);
		char *dir1 = parse_server_data_n(data[i], 4);
		int x = atoi(x1);
		int y = atoi(y1);
		int dir = atoi(dir1);
		if (strcmp(username, user) == 0) {
			focus(window, x, y);
		}
		if (type == 1)
			draw_player(window, username, x, y, dir);
		if (type == 2)
			draw_object(window, x, y);
	}
}

int analyse_event(sfRenderWindow *window, sfEvent event, char *user)
{
	char *me = get_my(user);

	if (sfRenderWindow_pollEvent(window, &event)) {
		if (event.type == sfEvtClosed) {
			printf("Close\n");
			player_disconnect(user);
			sfRenderWindow_close(window);
			return (1);
		}
		if (sfKeyboard_isKeyPressed(keyboard_up)) {
			send_move(user, "1");
		}
		if (sfKeyboard_isKeyPressed(keyboard_down)) {
			send_move(user, "2");
		}
		if (sfKeyboard_isKeyPressed(keyboard_left)) {
			send_move(user, "3");
		}
		if (sfKeyboard_isKeyPressed(keyboard_right)) {
			send_move(user, "4");
		}
		if (sfKeyboard_isKeyPressed(sfKeySpace)) {
			player_shoot(me);
		}
	}
	return (0);
}

int draw_(char *user)
{
	printf("Game Started\n");
	char **data;
	sfVideoMode mode = {width, height, 32};
	sfRenderWindow* window;
	sfEvent event;
	sfClock *clock;
	sfTime time;
	float seconds = 0.0;

	clock = sfClock_create();
	window = sfRenderWindow_create(mode, user, sfResize | sfClose, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
	while (sfRenderWindow_isOpen(window)) {
		time = sfClock_getElapsedTime(clock);
		seconds = time.microseconds / 1000000.0;
		if (seconds > 0.01) {
			data = parse_data();
			if (analyse_event(window, event, user) == 1)
				break;
			sfRenderWindow_clear(window, sfBlack);
			draw_from_server(window, data, user);
			sfRenderWindow_display(window);
			sfClock_restart(clock);
		}
	}
	sfRenderWindow_destroy(window);
	return (1);
}
