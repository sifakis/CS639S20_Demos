## Made by Kelton Halbert 
## for CS639 and compiles
## for GNU C++. Replace
## G++ with your compiler,
## and change -fopenmp to 
## be the compiler appropriate
## OpenMP linking
LINKOPTS = -fopenmp 
CC = g++

all: main Laplacian.cpp

Laplacian.o: Laplacian.cpp 
	$(CC) -std=c++11 -c -o Laplacian.o Laplacian.cpp $(LINKOPTS)

main: main.cpp Laplacian.o 
	$(CC) -std=c++11 -o main.exe main.cpp Laplacian.o $(LINKOPTS)

clean:
	rm -rf *.o 
