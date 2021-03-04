BIN = app
DIR = ./build

SRC = ./src/main.c

CC = gcc
CFLAGS-D = -O0 -o $(DIR)/$(BIN) -Wall -g
CFLAGS-R = -O2 -o $(DIR)/$(BIN)
LIBS = -lSDL2 -lGLEW -lGLU -lGL -lm

debug: $(DIR) $(SRC)
	$(CC) $(SRC) $(CFLAGS-D) $(LIBS)

release:
	$(CC) $(SRC) $(CFLAGS-R) $(LIBS)

$(DIR):
	mkdir $(DIR)

clean:
	rm -rf $(DIR)
