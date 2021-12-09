CC=zig cc
CXX=g++
CFLAGS=-target x86_64-windows-gnu 
LDFLAGS= -lwinhttp -lcrypt32 -lbcrypt -municode
PDB=-g
BIN=bin

all: implant

implant:
	$(CXX) implant.cpp base64.cpp rsa.cpp httpClient.cpp $(LDFLAGS)
http:
	g++ httpClient.cpp -lwinhttp -o http.o

clean:
	rm *.exe *.o
