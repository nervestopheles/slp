BIN = app
DIR = ./debug

SRC = ./src/main.c

CC = gcc
CFLAGS = -O0 -o $(DIR)/$(BIN) -Wall -g #-std=c99 -pedantic
LIBS = -lSDL2 -lGLEW -lGLU -lGL -lm

build: $(DIR) $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS)

$(DIR):
	mkdir $(DIR)

clean:
	rm -rf $(DIR)
