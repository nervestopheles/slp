BIN = LabOneApp
DIR = ./build
SRC = ./src/main.c

so-name = LabOneGui
SO = $(DIR)/lib$(so-name).so

RUN-CMD = echo "export LD_LIBRARY_PATH='.' && ./$(BIN)" > $(DIR)/run.sh
CC = gcc

CFLAGS-DEBUG = -O0 -o $(DIR)/$(BIN) -Wall -g3
CFLAGS-RELEASE = -O0 -o $(DIR)/$(BIN)
LIBS = -L"$(DIR)" -l$(so-name) -lSDL2 -lGLEW -lGLU -lGL -lm

release: $(SRC) $(DIR) $(SO)
	$(CC) $(SRC) $(CFLAGS-RELEASE) $(LIBS)
	$(RUN-CMD)

debug: $(SRC) $(DIR) $(SO)
	$(CC) $(SRC) $(CFLAGS-DEBUG) $(LIBS)
	$(RUN-CMD)

install: $(SO)
	cp $(DIR)/$(BIN) /usr/bin/
	cp $(SO) /usr/lib/

uninstall:
	rm -f /usr/bin/$(BIN)
	rm -f /usr/lib/lib$(so-name).so

clean:
	rm -rf $(DIR)

$(DIR):
	mkdir -p $(DIR)

$(SO):
	$(CC) -c -fpic -o ./build/$(so-name).o -O2 -Wall ./src/nuklear.c
	$(CC) -shared -o $(SO) ./build/$(so-name).o
