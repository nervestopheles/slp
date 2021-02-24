BIN = app
DIR = ./debug

SRC = ./src/main.c

CC = gcc
CFLAGS = -Wall -O0 -g -o $(DIR)/$(BIN) -std=c99 -pedantic
LIBS = -lSDL2 -lGLEW -lGLU -lGL -lm

build: $(DIR) $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS)

$(DIR):
	mkdir $(DIR)

clean:
	rm -rf $(DIR)
