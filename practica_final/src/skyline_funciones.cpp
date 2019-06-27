#include <iostream>
#include <fstream>
#include "skyline_funciones.h"
using namespace std;

/*	Método que inicializa los dos vectores dinámicos de la clase con el 
	número de edificios previamente inicializado en el constructor		*/
void SkyLine::Crea (){
	abscisas = new double [n];
	alturas = new double [n];
}

/*	Método que reserva memoria en los dos vectores dinámicos de la clase
	con el número de edificios que recibe el método como parámetros		*/
void SkyLine::ReservaMemoria (int tam){
	abscisas = new double [tam];
	alturas = new double [tam];
}

/*	Método que destruye los vectores dinámicos y hace que los punteros sean nulos */
void SkyLine::Destruye (){
	delete [] abscisas;
	abscisas = 0;
	delete [] alturas;
	alturas = 0;
}

/*	Método que copia en el objeto actual el skyline recibido como parámetro 	*/
void SkyLine::Copia(const SkyLine &otro_skyline){
	n = otro_skyline.n;

	for (int i = 0 ; i < n ; i++){
		abscisas[i] = otro_skyline.abscisas[i];
		alturas[i] = otro_skyline.alturas[i];
	}
}	

/*	Método que redimensiona los dos vectores dinámicos añadiendo una casilla más	*/
void SkyLine::Redimensiona (){
	double *new_abscisas = new double [n+1];
	double *new_alturas = new double [n+1];

	for (int i = 0 ; i < n ; i++){
		new_abscisas[i] = abscisas[i];
		new_alturas[i] = alturas[i];
	}

	abscisas = new_abscisas;
	alturas = new_alturas;
}

/*	Método que simplifica un skyline cuando este tiene dos 
	abscisas iguales, manteniendo la de mayor altura 	*/
void SkyLine::Simplificar (){
	for (int i = 0 ; i < n ; i++)			
		if (abscisas[i] == abscisas[i+1]){
			int j;
			if (alturas[i] < alturas[i+1] || alturas[i] == alturas[i+1])
				j = i;
			else
				j = i+1;

			for (int j = i ; j < n ; j++)
					abscisas[j] = abscisas[j+1];
			n--;
		}
}

/*	Método que mezcla dos skylines recibidos como parámetros superponiendo 
	uno sobre otro de modo que quede el de mayor altura 		 		*/
void SkyLine::MezclarUnico (const SkyLine &skyline_1, const SkyLine &skyline_2){
	int i = 0, j = 0;

	while (i < skyline_1.n && j < skyline_2.n){
		if (skyline_1.abscisas[i] < skyline_2.abscisas[j]){
			Redimensiona();
			abscisas[n] = skyline_1.abscisas[i];
			alturas[n] = skyline_1.alturas[i];
			n++;
			i++;
		}
		else{
			Redimensiona();
			abscisas[n] = skyline_2.abscisas[j];
			alturas[n] = skyline_2.alturas[j];
			n++;
			j++;
		}
	}

	// Comprueba qué vector se ha quedado sin elementos
	if (i == skyline_1.n)
		for (int k = j ; k < skyline_2.n ; k++){
			Redimensiona();
			abscisas[n] = skyline_2.abscisas[k];
			alturas[n] = skyline_2.alturas[k];
			n++;
		}
	else
		for (int k = i ; k < skyline_1.n ; k++){
			Redimensiona();
			abscisas[n] = skyline_1.abscisas[k];
			alturas[n] = skyline_1.alturas[k];
			n++;
		}
		
	Simplificar ();
}

// Constructor por defecto
SkyLine::SkyLine (){
	n = 0;
	Crea();
}

// Constructor con parámetros
SkyLine::SkyLine (double abscisa_1, double abscisa_2, double altura){
	n = 2;
	Crea();

	abscisas[0] = abscisa_1;
	abscisas[1] = abscisa_2;
	alturas[0] = altura;
	alturas[1] = 0;
}

// Constructor de copia
SkyLine::SkyLine (const SkyLine &otro_skyline){
	ReservaMemoria (otro_skyline.n);
	Copia(otro_skyline);
}	

// Destructor
SkyLine::~SkyLine (){
	Destruye();
}

/*	Método que recibe un valor de abscisa y devuleve la altura en ese punto */
double SkyLine::Altura (double abscisa){
	double altura = 0.0;
	bool altura_encontrada = false;

	for (int i = 0 ; i < n && !altura_encontrada ; i++)
		if (abscisa >= abscisas[i] && abscisa < abscisas[i+1]){
			altura = alturas[i];
			altura_encontrada = true;
		}
	
	return altura;
}

/*	Método que establece un nuevo punto y altura 	*/
void SkyLine::SetEdificios (double abscisa, double altura){
	if ((abscisa > abscisas[n-1] || n == 0) && altura >= 0){
		Redimensiona();

		abscisas[n] = abscisa;
		alturas[n] = altura;
		n++;
	}
}

/*	Método que imprime un skyline */
void SkyLine::Imprime (){
	for (int i = 0 ; i < n ; i++)
		cout << abscisas[i] << " - " << alturas[i] << endl;
	cout << endl;
}

// Sobrecarga del operador de asignación
SkyLine & SkyLine::operator=(const SkyLine &otro_skyline){
	Destruye();
	ReservaMemoria (otro_skyline.n);
	Copia(otro_skyline);
	return (*this);
}

/*	Sobrecarga del operador de suma
	Suma dos skylines 			 */
SkyLine SkyLine::operator+(const SkyLine &skyline_suma){
	SkyLine resultado;
	resultado.MezclarUnico(*this,skyline_suma);

	return resultado;
}

// Sobrecarga del operador de extracción para que devuelva un skyline
ostream& operator<<(ostream &flujo, const SkyLine &skyline){
	for (int i = 0 ; i < skyline.n ; i++)
		flujo << skyline.abscisas[i] << " - " << skyline.alturas[i] << endl;
	flujo << endl;

	return flujo;
}

// Sobrecarga del operador de inserción para leer un skyline
istream& operator>>(istream &flujo, SkyLine &skyline){
	int num_abscisas;
	double abscisa, altura;
	flujo >> num_abscisas;

	for (int i = 0 ; i < num_abscisas ; i++){
		flujo >> abscisa >> altura;
		skyline.SetEdificios (abscisa, altura);
	}

	return flujo;
}

/*	Función que guarda un skyline en un fichero cuyo nombre se recibe
	como parámetro y que es introducido en tiemo de ejecución 		*/
int Salvar (char *nombre_fich, const SkyLine &skyline){
	ofstream outData;
	outData.open(nombre_fich);
	outData << skyline;
	outData.close();

	return 0;
}

/*	Función que carga un skyline en un objeto de la clase SkyLine desde un fichero
	cuyo nombre se recibe como parámetro y que es introducido en tiemo de ejecución */
int Cargar (char *nombre_fich, SkyLine &skyline){
	ifstream inData;
	inData.open(nombre_fich);
	inData >> skyline;
	inData.close();

	return 0;
}