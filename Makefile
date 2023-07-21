CC = g++
CFLAGS = -Wall 

all: main

main: todoizerrr.cpp todoizerrr.o
	$(CC) $(CFLAGS) todoizerrr.cpp -o todoizerrr.exe