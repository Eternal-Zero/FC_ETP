#include "Estructuras.hpp"
#include <iostream>

void Node::set(int dom){
	valor=dom;
}

int Node::get(){
	return valor;
}

void Node::add(int filter){
	forbiden.push_back(filter);
}

int Node::valid(int dom){
	for (long unsigned int i=0;i<forbiden.size();i++){
		if(dom==forbiden[i]){
			return 0;
		}
	}
	return 1;
}

void Node::Rollback(){
	if (!forbiden.empty()){
		forbiden.pop_back();
	}
}
void Node::print(){
	for(auto i=forbiden.begin();i!=forbiden.end();i++){
		cout << *i << endl;
	}
	cout << "----"<<endl;
}


void Alumno::add(int prueba){
	pruebas.push_back(prueba);
}

vector<int> Alumno::test(){
	return pruebas;
}
	

Matriz::Matriz(){
	size=0;
	matriz=NULL;
}


Matriz::Matriz(int s){
	size = s;
	matriz= new int*[s];
	for (int i=0; i<s;i++){
		int* temp= new int[s]; 
		temp[0] = {0};
		matriz[i] = temp;
	}
}
Matriz::~Matriz(){
	for (int i=0; i<size;i++){
		delete [] matriz[i];
	}
	delete [] matriz;
}

void Matriz::conflict(int f, int c){
	if(matriz!=NULL){
		matriz[f-1][c-1]=1;
	}
}

int Matriz::check(){
	int valid=1;
	if (matriz==NULL){
		valid=0;
	}
	return valid;
}

int Matriz::get(int f, int c){
	return matriz[f-1][c-1];
}