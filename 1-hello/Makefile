Out.txt : main
	./main > Out.txt

main : main.o
	${CXX} main.o -o main

main.o : main.cc
	${CXX} -c main.cc -o main.o

clean : 
	rm --force main main.o Out.txt

test :
	echo CXX
	echo ${CXX}