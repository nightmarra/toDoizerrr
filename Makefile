CXX = g++
CXXFLAGS = -Wall 

all: main

main: todoizerrr.cpp todoizerrr.o
	$(CXX) $(CXXFLAGS) todoizerrr.cpp -o todoizerrr.exe