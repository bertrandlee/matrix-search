CC = g++
CFLAGS = -Wall
OBJECTS = GenerateMatrix.o

all: genmatrix

GenerateMatrix.o: GenerateMatrix/GenerateMatrix/GenerateMatrix.cpp
	$(CC) $(CFLAGS) -c GenerateMatrix/GenerateMatrix/GenerateMatrix.cpp 

genmatrix: $(OBJECTS)
	$(CC) $(OBJECTS) -o genmatrix

clean:
	rm -f *.o genmatrix