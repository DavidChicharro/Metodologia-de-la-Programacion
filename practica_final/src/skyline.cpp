/* Skyline */
#include <iostream>
#include <fstream>
#include "skyline_funciones.h"
using namespace std;


int main(){
	char nombre_fich_salvar[100], nombre_fich_cargar[100];
	double altura;
	SkyLine skyline;
	SkyLine skyline_cargar;
	SkyLine resultado;

	cin >> skyline;								// Se introduce el skyline
	SkyLine skyline_2 = skyline;				// Se crea un nuevo skyline asignando uno ya existente
	SkyLine skyline_salvar(skyline);

	altura = skyline.Altura(3);					// Método que devuelve la altura
	cout << "\nAltura: " << altura << endl;

	cout << skyline_2;							// Imprime un skyline


	cout << "Nombre del fichero para salvar: ";
	cin >> nombre_fich_salvar;						// Se introduce el nombre del fichero en el que se quiere guardar el skyline
	Salvar(nombre_fich_salvar, skyline_salvar);		// Guarda un skyline en un fichero cuyo nombre se ha elegido previamente

	cout << "Nombre del fichero para cargar: ";
	cin >> nombre_fich_cargar;						// Se introduce el nombre del fichero desde el que se quiere cargar el skyline
	Cargar(nombre_fich_cargar, skyline_cargar);  	// Carga un skyline desde el fichero cuyo nombre se ha elegido previamente
	cout << "Fichero cargado: " << endl << skyline_cargar;		// Se imprime el fichero cargado

	resultado = skyline + skyline_cargar;							// Suma de dos skylines
	cout << "Superposicion de skylines " << endl << resultado;		// Se imprime el resultado de la suma

	return 0;
}