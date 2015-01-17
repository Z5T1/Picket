CC = gcc
OBJECTS = \
	PicketAPI.o \
	event/EventServices.o
	
libpicket.a: $(OBJECTS)
	ar -cvr libpicket.a $(OBJECTS)

PicketAPI.o: PicketAPI.c PicketAPI.h
	gcc -I./ -c PicketAPI.c -o PicketAPI.o

event/EventServices.o: event/EventServices.c event/EventServices.h
	gcc -I./ -c event/EventServices.c -o event/EventServices.o
