CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lm

# Default target
all: Out.txt

Out.txt : main
	./main > Out.txt

# Link the executable
# $@ = main, $^ = all three .o files
main : main.o ../eps/sfuns.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Compile individual objects
main.o : main.cc vec.h ../eps/sfuns.h
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

../eps/sfuns.o : ../eps/sfuns.cc ../eps/sfuns.h
	$(CXX) $(CXXFLAGS) -c ../eps/sfuns.cc -o ../eps/sfuns.o

.PHONY: clean

clean : 
	$(RM) main *.o Out.txt ../eps/sfuns.o