CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lm

# Default target
all: Out.txt

Out.txt : main
	./main > Out.txt

# Link the executable
# $@ = main, $^ = all three .o files
main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Compile individual objects
main.o : main.cc
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

.PHONY: clean

clean : 
	$(RM) main *.o Out.txt ../eps/sfuns.o