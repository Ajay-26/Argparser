CC = g++
CFLAGS = -Wall -g -std=c++17
LINKER_FLAGS = -lm


main: main.o parser.o
	$(CC) main.o parser.o -o main $(CFLAGS) $(LINKER_FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp -o parser.o $(CFLAGS)