CC=g++ # the compiler name
CCFLAGS=-std=c++11 # flags passed to compiler
# the normal build rules
driver.o: PGMimageProcessor.h
	$(CC) $(CCFLAGS) driver.cpp -c
PGMimageProcessor.o: ConnectedComponent.h
	$(CC) $(CCFLAGS) PGMimageProcessor.cpp -c
ConnectedComponent.o: ConnectedComponent.h
	$(CC) $(CCFLAGS) ConnectedComponent.cpp -c
main.exe: driver.o PGMimageProcessor.o ConnectedComponent.o
	$(CC) $(CCFLAGS) driver.o -o main

run: main.exe
clean:
	rm -f *.o main.exe