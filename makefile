output: main.o sha256.o
	g++ main.o sha256.o -o main && main

main.o: main.cpp
	g++ -c main.cpp

sha256.o: hash/sha256.cpp hash/sha256.h
	g++ -c hash/sha256.cpp 