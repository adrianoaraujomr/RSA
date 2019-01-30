all: main

nano_rsa.o: nano_rsa.c nano_rsa.h
	gcc -c nano_rsa.c

main.o: main.c nano_rsa.o
	gcc -c main.c

main: main.o nano_rsa.o

clean:
	rm *.o
