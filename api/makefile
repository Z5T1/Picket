CC = gcc
OBJECTS = \
	PicketAPI.o \
	
#libpicket.a: $(OBJECTS)
#	ar -cvr libpicket.a $(OBJECTS)

PicketAPI.o: PicketAPI.c PicketAPI.h
	gcc -fPIC -I.root/ -c PicketAPI.c -o PicketAPI.o
