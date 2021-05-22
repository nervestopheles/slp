AppName = AppOne
LibName = NuklearBin
BuildDir = ./build

SRC = ./src/main.c
SO = $(BuildDir)/lib$(LibName).so

CC = gcc
CFlagsDebug = -O0 -o $(BuildDir)/$(AppName) -Wall -g3
CFlagsRelease = -O2 -o $(BuildDir)/$(AppName)
Libs = -L"$(BuildDir)" -l$(LibName) -lSDL2 -lGLEW -lGLU -lGL -lm

RunScript = echo "export LD_LIBRARY_PATH='.' && ./$(AppName)" > $(BuildDir)/run.sh

release: $(SRC) $(SO)
	$(CC) $(SRC) $(CFlagsRelease) $(Libs)
	$(RunScript)

debug: $(SRC) $(SO)
	$(CC) $(SRC) $(CFlagsDebug) $(Libs)
	$(RunScript)

install: $(SO)
	cp $(BuildDir)/$(AppName) /usr/bin/
	cp $(SO) /usr/lib/

uninstall:
	rm -f /usr/bin/$(AppName)
	rm -f /usr/lib/lib$(LibName).so

clean:
	rm -rf $(BuildDir)

$(SO):
	mkdir -p $(BuildDir)
	$(CC) -c -fpic -o $(BuildDir)/$(LibName).o -O2 -Wall ./src/nuklear.c
	$(CC) -shared -o $(SO) $(BuildDir)/$(LibName).o
	rm -f $(BuildDir)/$(LibName).o
