/*
** EPITECH PROJECT, 2018
** include.h
** File description:
** header file for the Demo for the AZERTY keyboard
*/

#ifndef MY_MMO_H_
#define MY_MMO_H_

#include <SFML/Network.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define server_ip ("10.15.192.116")
#define width (800)
#define height (600)
#define pixel_buffer (4)
#define keyboard_up (25)
#define keyboard_down (18)
#define keyboard_right (3)
#define keyboard_left (16)
void draw_username(sfRenderWindow *window, char *username, int x, int y);
float get_rotation(int dir);
void draw_player(sfRenderWindow *window, char *username, int x, int y, int dir);
void draw_object(sfRenderWindow *window, int x, int y);
void draw_map(sfRenderWindow *window);
void focus(sfRenderWindow *window, int x, int y);
void draw_from_server(sfRenderWindow *window, char **data, char *user);
int analyse_event(sfRenderWindow *window, sfEvent event, char *user);
int draw_(char *user);
void show_help(void);
int main(int ac, char **argv);
char *concat(char const *str1, char const *str2);
int get_arg_nb(char *argv);
char *set_string(char *argv, int old_i, int i);
char **set_args(char *argv, int nb);
char *parse_server_data_n(char *data, int a);
void player_disconnect(char *user);
void send_move(char *user, char *move);
void player_shoot(char *me);
char *get_my(char *user);
char **parse_data(void);
int register_(char *user, char *password);
char *register_user(void);
int login(char *user, char *password);
char *get_user(void);


#endif /* !INCLUDE_H_ */
