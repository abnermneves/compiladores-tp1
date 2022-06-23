all: main.o
	g++ -Wall *.cpp -o tp1.exe

clean:
	rm -r -f *.exe *.o

main.o: util.o main.cpp
	g++ -Wall  -c $^ -o $@

util.o: util.cpp
	g++ -Wall -c $^ -o $@
