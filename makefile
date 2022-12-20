

default: Estructuras.cpp main.cpp
	g++ -Wall Estructuras.cpp main.cpp -o ETP

clean:
	rm -f ETP