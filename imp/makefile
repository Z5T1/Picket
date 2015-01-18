CC = gcc
OBJECTS = \
	Console.o \
	event/EventServices.o

all:
	make $(OBJECTS)

Console.o: Console.c
	gcc -I.root/ -c Console.c -o Console.o

event/EventServices.o: event/EventServices.c
	gcc -I.root/ -c event/EventServices.c -o event/EventServices.o
