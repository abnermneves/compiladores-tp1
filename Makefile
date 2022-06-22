all: *.cpp
	g++ -Wall *.cpp -o tp1.exe

clean:
	rm *.exe