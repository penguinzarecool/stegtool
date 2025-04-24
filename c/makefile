build:
	gcc -c main.c -o main.o
	gcc -c encoding.c -o encoding.o
	gcc -c decoding.c -o decoding.o
	gcc main.o encoding.o decoding.o -o cstegtool
	rm -f *.o

clean:
	rm -f *.o cstegtool
