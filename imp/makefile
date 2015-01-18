CC = gcc
OBJECTS = \
	Console.o \
	event/EventServices.o

all:
	make $(OBJECTS)

Console.o: Console.c
	gcc -I../ -c Console.c -o Console.o

event/EventServices.o: event/EventServices.c
	gcc -I../ -c event/EventServices.c -o event/EventServices.o
