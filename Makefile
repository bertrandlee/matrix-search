CC = g++
CFLAGS = -Wall -Wno-sign-compare -I ./inc
GENMATRIX_OBJECTS = GenerateMatrix.o MyMatrix.o
SEARCHMATRIX_OBJECTS = SearchMatrix.o MyMatrix.o

all: genmatrix srchmatrix

GenerateMatrix.o: GenerateMatrix/GenerateMatrix/GenerateMatrix.cpp
	$(CC) $(CFLAGS) -c GenerateMatrix/GenerateMatrix/GenerateMatrix.cpp 

SearchMatrix.o: SearchMatrix/SearchMatrix/SearchMatrix.cpp
	$(CC) $(CFLAGS) -c SearchMatrix/SearchMatrix/SearchMatrix.cpp 

MyMatrix.o: shared/MyMatrix.cpp
	$(CC) $(CFLAGS) -c shared/MyMatrix.cpp 	

genmatrix: $(GENMATRIX_OBJECTS)
	$(CC) $(GENMATRIX_OBJECTS) -o genmatrix

srchmatrix: $(SEARCHMATRIX_OBJECTS)
	$(CC) $(SEARCHMATRIX_OBJECTS) -o srchmatrix

clean:
	rm -f *.o genmatrix srchmatrix SearchMatrix.txt
