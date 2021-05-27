AppName = labTwo
BuildDir = ./build

SRC = ./src/main.c

CC = gcc
CFlagsDebug = -O0 -o $(BuildDir)/$(AppName) -Wall -g3
CFlagsRelease = -O2 -o $(BuildDir)/$(AppName)
Libs = -lSDL2 -lGL

release: $(SRC) $(BuildDir)
	$(CC) $(SRC) $(CFlagsRelease) $(Libs)

debug: $(SRC) $(BuildDir)
	$(CC) $(SRC) $(CFlagsDebug) $(Libs)

clean:
	rm -rf $(BuildDir)

$(BuildDir):
	mkdir -p $(BuildDir)