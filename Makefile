all: y86emul.o
	gcc y86emul.o -o y86emul
y86emul.o: y86emul.h y86emul.c
	gcc -c y86emul.c -o y86emul.o

clean:
	rm *.o y86emul
