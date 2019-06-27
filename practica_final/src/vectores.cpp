#include <iostream>
#include "vectores_funciones.h"
using namespace std;

int main(){
	const int TAM = 50;
	double v1[TAM];
	double v2[TAM];
	double v3[TAM];
	int util_v1 = 0, util_v2 = 0, util_v3 = 0;
	int elem_vect_salida;

	// Entrada de datos
	LeeVector(v1, util_v1);
	LeeVector(v2, util_v2);

	// Cómputos
	OrdenaVector(v1, util_v1);
	OrdenaVector(v2, util_v2);

	elem_vect_salida = MezclarUnico(v1, util_v1, v2, util_v2, v3, util_v3);

	// Salida de resultados
	cout << "\nElementos en el vector de salida: " << elem_vect_salida << endl;
	ImprimeVector(v3, util_v3);	

	return 0;
}