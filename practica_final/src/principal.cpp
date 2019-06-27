/*	Programa que lee desde la entrada estándar una secuencia con el contenido de la matriz y genera
	el archivo correspondiente. El nombre del archivo se especifica en la linea de órdenes. 	 */

#include <iostream>
#include <fstream>
#include "principal_funciones.h"
using namespace std;

int main(){
	char fich_salvar[30];
	MatrizDispersa matriz;

	// Entrada de datos
	cin >> matriz;

	// Salida de resultados
	cout << "\nIntroduzca el nombre del archivo en el que desea salvar la matriz: ";
	cin >> fich_salvar;
	Salvar (fich_salvar, matriz);

	return 0;
}