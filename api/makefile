CC = gcc
OBJECTS = \
	PicketAPI.o \
	
#libpicket.a: $(OBJECTS)
#	ar -cvr libpicket.a $(OBJECTS)

PicketAPI.o: PicketAPI.c PicketAPI.h
	gcc -fPIC -I../ -c PicketAPI.c -o PicketAPI.o
