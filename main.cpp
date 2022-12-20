#include "Estructuras.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <set>


int timeslot; /*se setea con la cantidad de timeslots*/
float penalty=-1; /*Si se llega a dar el caso que la primera solucion sea el peor caso, aka, timeslot=E,
				se verifica si el penalty es -1 para identificar que es la primera solucion y aceptarla*/
string filename;

vector<Alumno> init_alumns(string file){
	string last;
	string actual;
	string aux;
	int test;
	vector<Alumno> alumnos;
	Alumno* alum = new Alumno();
	fstream f;
	f.open(file);
	if(!f){
		cout << "Failed" << endl;
		return {};
	}
	getline(f, aux);
	stringstream temp(aux);
	temp >> last;
	temp >> test;
	alum->add(test);
	while(!f.eof()){
		getline(f, aux);
		if(aux==""){
			continue; /*Cuando termina de leer el archivo, lee un string vacio*/
		}
		stringstream temp(aux);
		temp >> actual;
		temp >> test;
		if (last != actual){
			alumnos.push_back(*alum);
			alum=new Alumno();
			alum->add(test);
			last=actual;
		}
		else{
			alum->add(test);
		}
	}
	alumnos.push_back(*alum); /*Agrega el ultimo nodo que quedo pendiente*/
	f.close();
	return alumnos;
}

int len_tests(string file){
	int val=0;
	string temp;
	fstream f;
	f.open(file);
	if (!f){
		return val;
	}
	while (getline(f, temp)){
		
		if (temp!=""){
			val+=1;
		}
		else{
			break;
		}
	}
	f.close();
	return val;
}

Matriz* conflictos(vector<Alumno> inscritos, int size){
	bool lock=false;
	if (size==0){
		Matriz* null = new Matriz();
		return null;
	}
	cout << size << endl;
	Matriz* conf = new Matriz(size);
	for(int i=0;i<size;i++){
		for(auto j=inscritos.begin(); j!=inscritos.end();j++){
			vector<int>aux = j->test();
			for(auto k=aux.begin(); k!=aux.end();k++){
				if(i==*k){ /*El alumno si debe rendir el examen i*/
					lock=true;
				}
				else if(i<*k && !lock){ /*Me pase, este alumno no tiene el examen i*/
					break;
				}
				else if(i<*k && lock){ /*Como debe rendir el examen i, marco el resto de pruebas*/
					conf->conflict(i, *k);
					conf->conflict(*k, i); /*La matriz es simetrica, ademas que por como se revisa la lista
											en la medida que se avanza, no revisa valores previos, los valores son ascendentes*/

				}

			}
			lock=false;
		}
	}
	return conf;
}

vector<Node>* solution(int size){
	vector<Node>* nodes=new vector<Node>();
	for (int i=0; i<size;i++){
		Node* temp=new Node();
		nodes->push_back(*temp);
	}
	return nodes;
}

float soft(vector<Alumno> calendar, vector<Node>* sol){
	float suma=0.0;
	vector<int> orden;
	for(long unsigned int i=0; i<calendar.size();i++){
		vector<int> aux=calendar[i].test();
		for (long unsigned int j=0; j<aux.size();j++){
			auto test=sol->begin()+aux[j]-1;
			orden.push_back(test->get()); /*Busco el bloque que le corresponde a la prueba j del alumno i
											Como los conjuntos estan ordenados, al calcular la diferencia entre
											los elementos, puedo saber el penalty del alumno en cuestion*/
		}
		for (long unsigned int j=0;j<orden.size()-1;j++){
			if(abs(orden[i]-orden[i+1])==1){ /*Bloques contiguos*/
				suma+=16;
			}
			else if(abs(orden[i]-orden[i+1])==2){ /*Bloque intermedio*/
				suma+=8;
			}
			else if(abs(orden[i]-orden[i+1])==3){ /*2 bloques*/
				suma+=4;
			}
			else if(abs(orden[i]-orden[i+1])==4){ /*3 bloques*/
				suma+=2;
			}
			else if(abs(orden[i]-orden[i+1])==5){ /*4 bloques*/
				suma+=1;
			}
		}
		orden.clear();
	}
	return suma/(float)calendar.size();
}

/*Solo escribe en los archivos si encuentra un nuevo optimo, ya sea mejorando los timeslots o disminuyendo el penalty*/

void save_sol(vector<Node>* sol){
	/*DO*/
	fstream f;
	f.open("./Output/"+filename+".res",ios::app);
	f << timeslot << "\n";
	f << "-----------" << "\n";
	f.close();
	f.open("./Output/"+filename+".pen", ios::app);
	f << penalty << "\n";
	f << "-------------" << "\n";
	f.close();
	f.open("./Output/"+filename+".sol", ios::app);
	for (long unsigned int i=0; i<sol->size();i++){
		auto pos=sol->begin()+i;
		f << i+1 << " " << pos->get() << "\n";
	}
	f << "--------------" << "\n";
	f.close();
}

void eval(vector<Node>* sol, vector<Alumno> calendar){
	set<int> slot_num;
	for(auto i=sol->begin(); i<sol->end();i++){
		slot_num.insert(i->get());
	}
	/*Si es que se mejora el timeslots*/
	if (slot_num.size()<(long unsigned int)timeslot){
		cout << "Timeslots:" << slot_num.size() << endl;
		timeslot=slot_num.size();
		/*Reinicio el penalty para mejorar la solucion en otras iteraciones*/
		penalty=soft(calendar, sol);
		save_sol(sol);
		/*Registrar solucion*/
	}
	/*Si es que no se mejora el timeslot pero si la penalizacion*/
	else if(slot_num.size()==(long unsigned int)timeslot){
		float temp=soft(calendar, sol);
		if (temp==-1 || temp<penalty){
			cout << "Penalty:" << temp << endl;
			penalty=temp;
			save_sol(sol);
		}
	}
}


void FC(vector<Node>* sol, vector<Alumno> calendar, Matriz* conflictos, int nodo, int max){
	vector<int>filtered;
	for (int i=1;i<=max; i++){
		/*Revisa si el valor del dominio a tomar es valido*/
		auto val=sol->begin()+nodo;
		if(val->valid(i)){
			val->set(i);
		}
		else{
			continue;
		}
		if(nodo == max-1){
			eval(sol, calendar);

		}
		else{
			/*Filtra el dominio del resto de nodos*/
			for (int j=nodo+1;j<max;j++){
				if(conflictos->get(nodo+1, j+1)){ /*Esto funciona con los numeros de prueba, no con los indices de las estructuras*/
					auto conf=sol->begin()+j;
					conf->add(i);
					filtered.push_back(j);
					/*Para este problema en particular no existe un return anticipado por dominios vacios
					puesto que todas las pruebas deben ser agendadas, se asume que pueden haber tantos timeslot
					como pruebas, por lo que en el peor de los casos, siempre va a existir un valor en el dominio*/
				}
			}
			/*Llamo a FC, siguiendo la logica de descender por el arbol*/
			FC(sol, calendar, conflictos, nodo+1, max);
			/*Deshago los filtros para considerar otro valor para este nodo*/
			for(long unsigned int k=0;k<filtered.size();k++){
				auto ind=sol->begin()+filtered[k];
				ind->Rollback();
			}
			filtered.clear();
		}
	}
}

int main(int argc, char **argv){
	if (argc==2){
		filename=argv[1];
		fstream f;
		f.open("./Input/"+filename+".stu");
		cout << "/Input/" << filename << ".stu" << endl;
		if (f){
			cout << "Existe" << endl;
		}
		else{
			cout << "No existe" << endl;
			exit(2);
		}
		f.close();
	}
	else{
		cout << "No se indico la instancia del problema a ejecutar o se entregaron mas parametros que los que corresponde" << endl;
		exit(1);
	}
	vector<Alumno> result;
	result=init_alumns("./Input/"+filename+".stu");
	int size=len_tests("./Input/"+filename+".exm");
	timeslot=size;
	Matriz* temp = conflictos(result, size);
	vector<Node>* solt;
	solt=solution(size);
	FC(solt, result, temp, 0, solt->size());

	return 0;
};