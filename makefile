CC=gcc
COMPILEFLAGS=-Wall -c
SRC=src
LIB=lib
BIN=bin

all:link

link:main echo test
	$(CC) $(LIB)/echo.o $(LIB)/main.o $(LIB)/test.o -o $(BIN)/main
	
main:
	$(CC) $(COMPILEFLAGS) $(SRC)/main.c -o $(LIB)/main.o

echo:
	$(CC) $(COMPILEFLAGS) $(SRC)/echo.c -o $(LIB)/echo.o

test:
	$(CC) $(COMPILEFLAGS) $(SRC)/test.c -o $(LIB)/test.o

clean:
	rm -f mycli