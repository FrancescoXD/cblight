CC = gcc
CCFLAGS = -Wall -Wextra -Werror -pedantic
FILES = src/main.c
OUTPUT = ./build/cblight
LIBS = -I./include/

.PHONY: build clean

clean:
	rm -rf *.o

build:
	$(CC) $(FILES) -o $(OUTPUT) $(CCFLAGS)
