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
	mkdir db
	npm install

info:
	ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1'