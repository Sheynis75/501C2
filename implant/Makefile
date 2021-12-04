CC=zig cc
CXX=g++
CFLAGS=-target x86_64-windows-gnu 
LDFLAGS= -lwinhttp -municode
PDB=-g
BIN=bin

all: implant

implant:
	$(CXX) implant.cpp httpClient.cpp $(LDFLAGS)
http:
	g++ httpClient.cpp -lwinhttp -o http.o

clean:
	rm *.exe *.o
