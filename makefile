CC=gcc
CFLAGS=-Wall
COMPILEFLAGS=-Wall -c -I./include
SRC=src
INCLUDE=include
LIB=lib
BIN=bin

SOURCES=$(SRC)/main.c $(SRC)/redirection.c $(SRC)/pipeline.c $(SRC)/command.c
OBJECTS=$(SOURCES:$(SRC)/%.c=$(LIB)/%.o)

all: link

link: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/shell

$(LIB)/%.o: $(SRC)/%.c
	$(CC) $(COMPILEFLAGS) $< -o $@

clean:
	rm -rf $(BIN)
	rm -rf $(LIB)