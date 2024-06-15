all: prog.exe

prog.exe: main.o
	gcc -o prog.exe main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f prog.exe main.o
