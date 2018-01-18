/*
** EPITECH PROJECT, 2018
** include.h
** File description:
** header file for the Demo
*/

#ifndef MY_MMO_H_
#define MY_MMO_H_

#include <SFML/Network.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void player_disconnect(char *user);
int get_arg_nb(char *argv);
char *set(char *argv, int old_i, int i);
char **set_args(char *argv, int nb);
char **parse_data(void);
char *parse_(char *data, int a);
void draw_username(sfRenderWindow *window, char *username, int x, int y);
float get_rotation(int dir);
void draw_player(sfRenderWindow *window, char *username, int x, int y, int dir);
void draw_object(sfRenderWindow *window, int x, int y);
void draw_from_server(sfRenderWindow *window, char **data, char *user);
void clear_pixel(sfTexture *texture, sfUint8 *pixels);
int draw_(char *user);
char *concat(char const *str1, char const *str2);
int login(char *user, char *password);
int register_(char *user, char *password);
char *register_user(void);
char *get_user(void);
void player_disconnect(char *user);
void send_move(char *user, char *move);
void player_shoot(char *me);
char *get_my(char *user);
int main(int ac, char **argv);

#endif /* !INCLUDE_H_ */
