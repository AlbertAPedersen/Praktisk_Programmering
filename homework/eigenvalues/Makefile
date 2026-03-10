CXX=g++ -std=c++23  #Compiler and standard something?
CXXFLAGS = -Wall -Wextra  -O3 #-Werror #Flags for debugging
LDLIBS += -lstdc++ -lm #Links libraries that are already linked

packages = ../packages/matrix_QR.h jacobi.h
all : out.txt
	cat out.txt

out.txt : main
	./main > $@

#times.txt : main\
	> $@\
	for N in $$(seq 100 100 2200); do \
		time --format "$$N %e" --output $@ --append \
		./$< -size $$N 1>out ;\
	done 


main : main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

main.o : main.cc $(packages) Makefile
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

clean : 
	$(RM) main *.o out.txt plot.svg times.txt