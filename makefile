all: setup link

setup:
	mkdir -p bin
	mkdir -p lib

link: lib/main.o lib/redirection.o lib/pipeline.o lib/command.o
	gcc lib/main.o lib/redirection.o lib/pipeline.o lib/command.o -o bin/shell

lib/main.o: src/main.c
	gcc -Wall -c -I./include src/main.c -o lib/main.o

lib/redirection.o: src/redirection.c
	gcc -Wall -c -I./include src/redirection.c -o lib/redirection.o

lib/pipeline.o: src/pipeline.c
	gcc -Wall -c -I./include src/pipeline.c -o lib/pipeline.o

lib/command.o: src/command.c
	gcc -Wall -c -I./include src/command.c -o lib/command.o

clean:
	rm -rf bin
	rm -rf lib