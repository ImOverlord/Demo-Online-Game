##
## EPITECH PROJECT, 2017
## 104intersection
## File description:
## Makefile
##

NAME	=	mmo

INCLUDE	=	include

SRC	=	./src/client.c			\
		./src/draw.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -pedantic -I./include -lc_graph_prog

OFLAGS	=	-Wall -pedantic -I./include -lc_graph_prog

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -c $(SRC) $(OFLAGS)
		gcc $(CFLAGS) -lm *.o -o $(NAME) 

clean:	
		rm -f $(OBJ)
		rm -f *.o

fclean:		clean
		rm -f $(NAME)

re:		fclean all