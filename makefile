CC = gcc
OBJECTS = \
	picket.o \
	implementation.o \
	net.o \
	handlers.o \
	sessions.o \
	libs/varint.o \
	packets/packet.o \
	packets/generic_packet.o \
	packets/connect_packet.o \
	packets/chat_packet.o \
	imp/event/EventServices.o

picket: $(OBJECTS)
	gcc $(OBJECTS) -o picket -lpcap -ldl
	
implementation.o: implementation.c implementation.h
	gcc -c implementation.c -o implementation.o
	
net.o: net.c net.h
	gcc -c net.c -o net.o

picket.o: picket.c picket.h
	gcc -c picket.c -o picket.o
	
handlers.o: handlers.c handlers.h
	gcc -c handlers.c -o handlers.o
	
sessions.o: sessions.c sessions.h
	gcc -c sessions.c -o sessions.o

