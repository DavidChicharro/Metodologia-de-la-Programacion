#include <iostream>
#include "vectores_funciones.h"
using namespace std;

void LeeVector (double v[], int &util_v){
	const int TERMINADOR = -1.0;
	double numero;

	cout << "\nIntroduce elementos hasta el terminador " << TERMINADOR << ": " << endl;
	cin >> numero;

	while (numero != TERMINADOR){
		v[util_v] = numero;
		util_v++;
		cin >> numero;
	}
}

void EliminaRepetidos (double v[], int &util_v){
	for (int i = 0 ; i < util_v ; i++){
		if (v[i] == v[i+1]){
			for (int j = i+1 ; j < util_v ; j++)
				v[j] = v[j+1];
			util_v--;
		}
	}
}

void OrdenaVector (double v[], int &util_v){
	double a_desplazar;
	int izda, i;

	for (izda = 1 ; izda < util_v; izda++){
		a_desplazar = v[izda];

		for (i = izda; i > 0 && a_desplazar < v[i-1]; i--)
			v[i] = v[i-1];
		
		v[i] = a_desplazar;
	}

	EliminaRepetidos (v, util_v);
}



int MezclarUnico (double v1[], int util_v1, double v2[], int util_v2, double v_ord[], int &util_v_ord){
	int i = 0, j = 0;

	while (i < util_v1 && j < util_v2){
		if (v1[i] < v2[j]){
			v_ord[util_v_ord] = v1[i];
			i++;
			util_v_ord++;
		}
		else{
			v_ord[util_v_ord] = v2[j];
			j++;
			util_v_ord++;
		}
	}

	// Preguntar qué vector se ha quedado sin elementos
	if (i == util_v1)
		for (int k = j ; k < util_v2 ; k++){
			v_ord[util_v_ord] = v2[k];
			util_v_ord++;
		}
	else
		for (int k = i ; k < util_v1 ; k++){
			v_ord[util_v_ord] = v1[k];
			util_v_ord++;
		}
		
	EliminaRepetidos (v_ord, util_v_ord);

	return util_v_ord;
}

void ImprimeVector(double v[], int util_v){
	cout << endl;
	for (int i = 0 ; i < util_v ; i++)
		cout << v[i] << "  ";
	cout << endl;
}