##
## EPITECH PROJECT, 2017
## my_firstmmo_2017
## File description:
## Makefile
##

NAME	=	mmo

INCLUDE	=	include

SRC	=	./src/client_http/client_http_disconnect.c	\
		./src/client_http/client_http_login.c		\
		./src/client_http/client_http_register.c	\
		./src/client_http/client_server_com.c		\
		./src/client.c					\
		./src/draw.c					\
		./src/server_data_parsing.c			\
		./src/string_functions.c

TNAME	=	mmo_test

TSRC	=	./test/http_check.c

TOBJ	=	$(TSRC:.c=.o)

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -pedantic -lc_graph_prog -I./include

OFLAGS	=	-Wall -pedantic -lc_graph_prog 

TFLAGS	=	-Wall -pedantic -lc_graph_prog -lcriterion --coverage

all:
		gcc -c $(SRC) $(OFLAGS) -I./lang_pack/en_keyboard/
		gcc $(OFLAGS) -I./lang_pack/en_keyboard/ -lm *.o -o $(NAME) 

clean:	
		rm -f $(OBJ)
		rm -f *.o

fclean:		clean
		rm -f $(NAME)

re:		fclean all

test:		$(TOBJ)
		gcc $(TFLAGS) -lm $(TOBJ) -o $(TNAME)
		rm $(TOBJ)
		./$(TNAME)
		mv $(TNAME) ./test

test_clean:	
		rm ./test/*.gc*
		rm ./test/$(TNAME)

###### KEYBOARD

fr	:
		gcc -c $(SRC) $(OFLAGS) -I./lang_pack/fr_keyboard/
		gcc $(CFLAGS) -I./lang_pack/en_keyboard/ -lm *.o -o $(NAME)

en:
		gcc -c $(SRC) $(OFLAGS) -I./lang_pack/en_keyboard/
		gcc $(CFLAGS) -I./lang_pack/en_keyboard/ *.o -o $(NAME) 