output: main.o sha256.o header/dataStructure.h header/display.h header/fileHandling.h header/functions.h header/validation.h
	g++ main.o sha256.o -o main && main

main.o: main.cpp
	g++ -c main.cpp

sha256.o: hash/sha256.cpp hash/sha256.h
	g++ -c hash/sha256.cpp 


