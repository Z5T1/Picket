foo.so: foo.o
	gcc -shared -o foo.so foo.o .root/api/PicketAPI.o

foo.o: foo.c
	gcc -I.root/api -fPIC -c foo.c -o foo.o
