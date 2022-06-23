all: main.o
	g++ -Wall *.cpp -o tp1.exe

tp1: main.o
	g++ -Wall -o tp1 main.o

clean:
	rm -r -f *.exe *.o

main.o: util.o main.cpp
	g++ -Wall -c $^ -o $@

util.o: util.cpp
	g++ -Wall -c $^ -o $@
