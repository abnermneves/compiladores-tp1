all: main.o
	g++ -Wall *.cpp -o tp1.exe

clean:
	rm *.exe

main.o: util.o main.cpp
	g++ -Wall  -c $^ -o $@

util.o: util.cpp
	g++ -Wall -c $^ -o $@
