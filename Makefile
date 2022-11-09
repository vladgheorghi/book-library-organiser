CC=gcc
CFLAGS= -Wall -Wextra -std=c99
DEBUG= -g
VGRINDFLAGS=--track-origins=yes --leak-check=full --show-leak-kinds=all -s

build:
	$(CC) $(DEBUG) $(CFLAGS) *.c -o main

run:
	./main

clean:
	rm -rf *.o main

valgrind:
	valgrind $(VGRINDFLAGS) ./main

pack:
	zip 312CA_Gheorghiu_Vlad_SDTema2 *.c *.h README Makefile