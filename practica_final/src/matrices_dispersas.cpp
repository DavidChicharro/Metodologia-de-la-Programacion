#include <iostream>
#include <fstream>
#include "matrices_dispersas_funciones.h"
using namespace std;

int main(){
	int fil, col, util = 0;
	int valor_umbral;
	double *ptr_datos_matriz;
	char fich_cargar[30], fich_salvar[30];

	int filas[3] = {0,1,2};
	int columnas[3] = {0,1,2};
	double valores[3] = {1,2,3};
	MatrizDispersa matriz_1(3,3,filas,columnas,valores,3);		// Construcción de la matriz con parámetros
	MatrizDispersa matriz_3;
	MatrizDispersa matriz_res;
	MatrizDispersa matriz_poda;

	// Entrada de datos
	cout << "Construccion de una matriz." << endl
		 << "Indique el numero de filas y columnas: ";
	cin >> fil >> col;
	ptr_datos_matriz = new double [fil*col];
	cout << "Introduce un vector para convertir en una matriz dispersa: " << endl;
	do{
		cin >> ptr_datos_matriz[util];
		util++;
	} while (util < fil*col);

	MatrizDispersa matriz_2(fil, col, ptr_datos_matriz);		// Construcción de la matriz mediante un puntero de datos

	cout << "\nIntroduzca el nombre del archivo que desea cargar: ";
	cin >> fich_cargar;
	Cargar (fich_cargar, matriz_3);

	cout << "\nIntroduzca el nombre del archivo que desea cargar (matriz poda): ";
	cin >> fich_cargar;
	Cargar (fich_cargar, matriz_poda);
	cout << "\nIntroduzca un valor umbral." << endl
		 << "Por debajo este se eliminaran los elementos de la matriz: ";
	cin >> valor_umbral;


	// Cómputos
	matriz_poda.Podar(valor_umbral);
	matriz_res = matriz_1 + matriz_3;


	// Salida de resultados
	cout << "\nIntroduzca el nombre del archivo en el que desea salvar la matriz: ";
	cin >> fich_salvar;
	Salvar (fich_salvar, matriz_res);

	cout << "\nMatriz 1:" << matriz_1 << endl;
	cout << "\nMatriz 2:" << matriz_2 << endl;
	cout << "\nMatriz 3:" << matriz_3 << endl;
	cout << "Matriz resultado:" << matriz_res << endl;
	cout << "Matriz podada:" << matriz_poda << endl;
	
	return 0;
}