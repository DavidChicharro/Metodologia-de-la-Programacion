#include <iostream>
#include <fstream>
#include "principal_funciones.h"
using namespace std;

void MatrizDispersa::Inicializa (int num_filas = 0, int num_columnas = 0, int tam = 0){
	nfilas = num_filas;
	ncolumnas = num_columnas;
	numeroValores = tam;
	valores = new Valor [numeroValores];
}

void MatrizDispersa::Destruir (){
	delete [] valores;
	valores = 0;
}

void MatrizDispersa::Redimensiona (int nueva_dim){
	int tope;
	Valor *new_valores = new Valor [numeroValores + nueva_dim];

	if (nueva_dim < 0)
		tope = numeroValores + nueva_dim;
	else
		tope = numeroValores;

	for (int i = 0 ; i < tope ; i++)
		new_valores[i] = valores[i];

	delete [] valores;
	valores = new_valores;
}

bool MatrizDispersa::Vacia (){
	bool matriz_vacia = false;

	if (nfilas == 0 && ncolumnas == 0 && numeroValores == 0)
		matriz_vacia = true;

	return matriz_vacia;
}

void MatrizDispersa::Asigna (int fil, int col, double val){
	Redimensiona (1);
	valores[numeroValores].fila = fil;
	valores[numeroValores].columna = col;
	valores[numeroValores].valor = val;
	numeroValores++;
}

MatrizDispersa::MatrizDispersa (){
	Inicializa();
}

MatrizDispersa::~MatrizDispersa (){
	Destruir ();
}

void MatrizDispersa::AsignarValor (int fila, int columna, double valor){
	bool encontrado = false;

	if (valor != 0.0){
		if (Vacia()){
			Asigna (fila, columna, valor);
			encontrado = true;
		}
		if (fila >= nfilas)
			nfilas = fila+1;
		if (columna >= ncolumnas)
			ncolumnas = columna+1;

		for (int i = 0 ; i < numeroValores && !encontrado; i++){
			if (valores[i].fila == fila && valores[i].columna == columna){
				valores[i].valor = valor;
				encontrado = true;
			}
			else{
				Asigna (fila, columna, valor);
				encontrado = true;
			}
		}
	}
	else{
		for (int i = 0 ; i < numeroValores && !encontrado ; i++)
			if (valores[i].fila == fila && valores[i].columna == columna){
				for (int j = i ; j < numeroValores ; j++)
					valores[j] = valores[j+1];
				encontrado = true;
				Redimensiona (-1);
				numeroValores--;
			}
	}
}

ostream& operator<<(ostream &flujo, const MatrizDispersa &matriz){
	flujo << "\nNumero de filas: " << matriz.nfilas << endl <<
			 "Numero de columnas: " << matriz.ncolumnas << endl <<
			 "Numero de valores significativos: " << matriz.numeroValores << endl;

	for (int i = 0 ; i < matriz.numeroValores ; i++)
		flujo << "Fila = " << matriz.valores[i].fila << ", " <<
				 "columna = " << matriz.valores[i].columna << ", " <<
				 "valor = " << matriz.valores[i].valor << endl;

	return flujo;
}

istream& operator>>(istream &flujo, MatrizDispersa &matriz){
	int fila, columna;
	double valor;

	// Se introducen los valores de la matriz (fila, columna y valor)" hasta introducir (0, 0, 0)
	flujo >> fila >> columna >> valor;
	while ( !(fila == 0 && columna == 0 && valor == 0.0) ){
		matriz.AsignarValor(fila, columna, valor);
		flujo >> fila >> columna >> valor;
	}

	return flujo;
}

int Salvar (char *nombre_fich, const MatrizDispersa &matriz){
	ofstream outData;
	outData.open(nombre_fich);
	outData << matriz;
	outData.close();

	return 0;
}