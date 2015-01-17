foo.so: foo.o
	gcc -shared -o foo.so foo.o ../api/PicketAPI.o

foo.o: foo.c
	gcc -I../api -fPIC -c foo.c -o foo.o
