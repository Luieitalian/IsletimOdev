CC=gcc
COMPILEFLAGS=-Wall -c
SRC=src
LIB=lib
BIN=bin

all:link

link:main echo
	$(CC) $(LIB)/echo.o $(LIB)/main.o -o $(BIN)/main
	
main:
	$(CC) $(COMPILEFLAGS) $(SRC)/main.c -o $(LIB)/main.o

echo:
	$(CC) $(COMPILEFLAGS) $(SRC)/echo.c -o $(LIB)/echo.o

clean:
	rm -f mycli