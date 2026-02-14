CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra #-Werror -O  #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

all : Out.txt
	cat $<

Out.txt : main
#	./main > Out.txt # Typed explicitly next line takes variable ($<) and target $@
	./$< > $@

main : main.o
main.o : 
