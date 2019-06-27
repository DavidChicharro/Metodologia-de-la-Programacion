/* Montar skyline */
#include <iostream>
#include <fstream>
#include "montar_funciones.h"
using namespace std;

int main(){
	char nombre_fich_salvar[100];
	SkyLine skyline;

	// Entrada de datos
	cin >> skyline;

	// Salida de resultados
	cout << "Nombre del fichero para salvar: ";
	cin >> nombre_fich_salvar;
	Salvar(nombre_fich_salvar, skyline);

	return 0;
}