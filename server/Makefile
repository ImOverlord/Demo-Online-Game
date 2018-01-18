##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Server Makefile
##

all:	db server

database:
	mongod --dbpath="./db"
	echo "DB"

server:
	node game_server.js

setup:
	npm install