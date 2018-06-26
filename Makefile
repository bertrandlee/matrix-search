CC = g++
CFLAGS = -Wall -Wno-sign-compare -I ./inc -std=c++11 -O3
GENMATRIX_OBJECTS = GenerateMatrix.o MyMatrix.o
SEARCHMATRIX_OBJECTS = SearchMatrix.o MyMatrix.o Search.o
SEARCHTESTS_OBJECTS = Search.o SearchTests.o MyMatrix.o

all: genmatrix srchmatrix srchtests

GenerateMatrix.o: GenerateMatrix/GenerateMatrix/GenerateMatrix.cpp
	$(CC) $(CFLAGS) -c GenerateMatrix/GenerateMatrix/GenerateMatrix.cpp 

SearchMatrix.o: SearchMatrix/SearchMatrix/SearchMatrix.cpp
	$(CC) $(CFLAGS) -c SearchMatrix/SearchMatrix/SearchMatrix.cpp 

SearchTests.o: SearchTests/SearchTests/SearchTests.cpp
	$(CC) $(CFLAGS) -c SearchTests/SearchTests/SearchTests.cpp 	

MyMatrix.o: shared/MyMatrix.cpp
	$(CC) $(CFLAGS) -c shared/MyMatrix.cpp 	

Search.o: shared/Search.cpp
	$(CC) $(CFLAGS) -c shared/Search.cpp 	

genmatrix: $(GENMATRIX_OBJECTS)
	$(CC) $(GENMATRIX_OBJECTS) -o genmatrix

srchmatrix: $(SEARCHMATRIX_OBJECTS)
	$(CC) $(SEARCHMATRIX_OBJECTS) -o srchmatrix

srchtests: $(SEARCHTESTS_OBJECTS)
	$(CC) $(SEARCHTESTS_OBJECTS) -o srchtests

clean:
	rm -f *.o genmatrix srchmatrix srchtests
