CC = gcc
CCFLAGS = -Wall -Wextra -Werror -pedantic
FILES = src/main.c
OUTPUT = ./build/cblight
LIBS = -I./include/

build:
	mkdir ./build/
	$(CC) $(FILES) -o $(OUTPUT) $(CCFLAGS) ${LIBS}

