CC = gcc
OBJECTS = \
	picket.o \
	net.o \
	handlers.o \
	sessions.o \
	libs/varint.o \
	packets/packet.o \
	packets/generic_packet.o \
	packets/connect_packet.o \
	packets/chat_packet.o \
	api/event/EventServices.o

picket: main.o
	gcc main.o -o picket -lpcap

main.o: $(OBJECTS)
	ld -r $(OBJECTS) -o main.o
	
net.o: net.c net.h
	gcc -c net.c -o net.o

picket.o: picket.c picket.h
	gcc -c picket.c -o picket.o
	
handlers.o: handlers.c handlers.h
	gcc -c handlers.c -o handlers.o
	
sessions.o: sessions.c sessions.h
	gcc -c sessions.c -o sessions.o

