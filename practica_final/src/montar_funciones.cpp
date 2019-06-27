#include <iostream>
#include <fstream>
#include "montar_funciones.h"
using namespace std;

void SkyLine::Crea (){
	abscisas = new double [n];
	alturas = new double [n];
}

void SkyLine::Destruye (){
	delete [] abscisas;
	abscisas = 0;
	delete [] alturas;
	alturas = 0;
}

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

SkyLine::SkyLine (){
	n = 0;
	Crea();
}

SkyLine::~SkyLine (){
	Destruye();
}

void SkyLine::SetEdificios (double abscisa1, double abscisa2, double altura){
	if ((abscisa1 >= abscisas[n-1] || n == 0) && altura >= 0){
		if (abscisa1 == abscisas[n-1]){
			alturas[n-1] = altura;
		}
		else{
			Redimensiona();
			abscisas[n] = abscisa1;
			alturas[n] = altura;
			n++;
		}
		Redimensiona ();
		abscisas[n] = abscisa2;
		alturas[n] = 0;
		n++;
	}
}

ostream& operator<<(ostream &flujo, const SkyLine &skyline){
	for (int i = 0 ; i < skyline.n ; i++)
		flujo << skyline.abscisas[i] << " - " << skyline.alturas[i] << endl;

	return flujo;
}

istream& operator>>(istream &flujo, SkyLine &skyline){
	int num_edificios;
	double abscisa1, abscisa2, altura;
	flujo >> num_edificios;

	for (int i = 0 ; i < num_edificios ; i++){
		flujo >> abscisa1 >> abscisa2 >> altura;
		skyline.SetEdificios (abscisa1, abscisa2, altura);
	}

	return flujo;
}

int Salvar (char *nombre_fich, const SkyLine &skyline){
	ofstream outData;
	outData.open(nombre_fich);
	outData << skyline;
	outData.close();

	return 0;
}