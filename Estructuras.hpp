#include <iostream>
#include <vector>

using namespace std; 

/*
La clase Node busca contener la informacion relativa de los nodos del arbol durante la ejecucion de FC, siendo un nodo el equivalente a una prueba.

Para ello el atributo valor corresponde a la asignacion del timeslot, se considera que cuando se llega a una hoja, el atributo valor de cada
nodo corresponde a la asignacion de timeslots final de dicha iteracion

Forbidden por su parte, almacena los valores del dominio que fueron filtrados, si su largo alcanza a la cardinalidad de pruebas, se realiza la poda de la rama y se devuelve a un punto donde aun exista factibilidad


*/


class Node{
	int valor; /*En este caso vendria a ser el valor del dominio asignado*/
	vector<int>forbiden; /*Corresponde a los valores del dominio que fueron filtrados*/

public:

	void set(int dom);

	int get();

	void add(int filter);

	int valid(int dom);

	void Rollback();
	void print();
};



/*
La clase alumno cumple 2 funciones, la primera es poder construir la matriz de conflictos y la segunda para el calulo de la penalizacion

Su unico atributo es un vector que contiene los id de las pruebas que debe rendir
*/

class Alumno{
	vector<int>pruebas; /*Corresponde a las pruebas que debe rendir el alumno*/

public:

	void add(int prueba);

	vector<int> test();
	
};	


/*
La matriz de conflictos, creo que no hace falta explicarla
*/

class Matriz{
	int size;
	int** matriz;

public:

	Matriz();
	Matriz(int s);
	~Matriz();

	void conflict(int f, int c);

	int check();

	int get(int f, int c);
};