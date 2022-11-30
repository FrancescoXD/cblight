CC = gcc
CCFLAGS = -Wall -Wextra -Werror -pedantic
MAIN = src/main.c
FILES = src/cblight.c
OUTPUT = ./build/cblight
LIBS = -Iinclude/

build:
	mkdir ./build/
	$(CC) -c $(FILES) -o build/cblight_o $(CCFLAGS) $(LIBS)
	$(CC) $(MAIN) build/cblight_o $(CCFLAGS) $(LIBS) -o $(OUTPUT)
	rm ./build/cblight_o

clean:
	rm -rf ./build/
