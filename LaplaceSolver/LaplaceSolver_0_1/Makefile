## Made by Kelton Halbert 
## for CS639 and compiles
## for GNU C++. Replace
## G++ with your compiler,
## and change -fopenmp to 
## be the compiler appropriate
## OpenMP linking
LINKOPTS = -fopenmp 
CFLAGS = -std=c++11
CC = g++

SRCS = $(filter-out main.cpp, $(wildcard *.cpp))
OBJS = $(SRCS:.cpp=.o) 


all: main.exe $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LINKOPTS)

main.exe: main.cpp $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LINKOPTS)

clean:
	rm -f *.o 
	rm -f *.exe
