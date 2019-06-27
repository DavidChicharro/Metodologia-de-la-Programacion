#include <iostream>
#include <fstream>
#include "matrices_dispersas_funciones.h"
using namespace std;

/*	Método que inicializa la matriz dispersa según los valores recibidos como 
	parámetros. Si no se asignan valores, se inicializa por defecto a 0		*/
void MatrizDispersa::Inicializa (int num_filas = 0, int num_columnas = 0, int tam = 0){
	nfilas = num_filas;
	ncolumnas = num_columnas;
	numeroValores = tam;
	valores = new Valor [numeroValores];
}

/*	Método que destruye el vector dinámico de los valores de la matriz 	*/
void MatrizDispersa::Destruir (){
	delete [] valores;
	valores = 0;
}

/*	Método que redimensiona el vector dinámico de los valores de la matriz dispersa,
	reduciendo o aumentando tantos valores como reciba el método como parámetro 	*/
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

/*	Método que copia en la matriz dispersa actual otra matriz que se recibe como parámetro 	*/
void MatrizDispersa::Copia(const MatrizDispersa &otra_matriz){
	for (int i = 0 ; i < numeroValores ; i++)
		valores[i] = otra_matriz.valores[i];
}

/*	Método que devuelve 'true' si la matriz está vacía, es decir,
	si el número de filas y columnas es 0 y si el vector dinámico 
	de valores no contiene ningún elemento						*/
bool MatrizDispersa::Vacia (){
	bool matriz_vacia = false;

	if (nfilas == 0 && ncolumnas == 0 && numeroValores == 0)
		matriz_vacia = true;

	return matriz_vacia;
}

/* 	Método auxiliar al método 'CombinarSuma' para añadir a la matriz resultado los
	elementos de las matrices que se suman cuyas posiciones (fila/columna) no coinciden	*/
void MatrizDispersa::AniadirSuma (const MatrizDispersa &matriz, int &numero_valores){
	double nuevo_valor;
	bool valor_doble = false;

	for (int i = 0 ; i < matriz.numeroValores ; i++){						// Se recorren los valores de la segunda matriz
		valor_doble = false;
		for (int j = 0 ; j < numeroValores && !valor_doble; j++){			// Se recorren los valores del vector-c local
			// Se comprueba si no coinciden las posiciones
			if ( !(matriz.valores[i].fila == valores[j].fila &&
				matriz.valores[i].columna == valores[j].columna) ) 	
				valor_doble = false;
			else
				valor_doble = true;
		}				

		// Si el elemento de la segunda matriz no se había añadido, se añade
		if (!valor_doble){											
			nuevo_valor = matriz.valores[i].valor;
			AsignarValor (matriz.valores[i].fila, matriz.valores[i].columna, nuevo_valor);
			numero_valores++;
		}
	}
}

/*	Método auxiliar al método 'AsignarValor' para asignar valores a la matriz dispersa	*/
void MatrizDispersa::Asigna (int fil, int col, double val){
	Redimensiona (1);
	valores[numeroValores].fila = fil;
	valores[numeroValores].columna = col;
	valores[numeroValores].valor = val;
	numeroValores++;
}


/*	Constructor por defecto	 */
MatrizDispersa::MatrizDispersa (){
	Inicializa();
}

/*	Constructor con parámetros. Recibe dos enteros con las dimensiones de la matriz, 
	junto con tres vectores-C y un entero que indica sus tamaños. Cada posicion de 
	los vectores corresponde a una tripleta fila/columna/valor de la matriz.	 */
MatrizDispersa::MatrizDispersa (int numero_filas, int numero_columnas, const int v_fila[], const int v_columna[], const double v_valor[], int tamanio){
	if (tamanio <= numero_filas*numero_columnas){
		bool continuar = true;

		// Se comprueba que todos los valores introducidos sean válidos
		for (int i = 0 ; i < tamanio && continuar; i++){
			if(v_fila[i] < tamanio && v_columna[i] < tamanio && v_valor[i] != 0.0)
				continuar = true;
			else
				continuar = false;
		}
		if (continuar){			
			Inicializa (numero_filas, numero_columnas, tamanio);
			for (int i = 0 ; i < numeroValores ; i++){
				valores[i].fila = v_fila[i];
				valores[i].columna = v_columna[i];
				valores[i].valor = v_valor[i];
			}
		}			
	}
}

/*	Constructor que recibe como parámetros las filas y columnas y un tercer parámetro opcional, 
	que es un puntero a los datos. Este puntero tiene 0 como valor por defecto (estará 
	inicializado a ese valor) en cuyo caso representa una matriz con todos los valores a 0.	*/
MatrizDispersa::MatrizDispersa (int numero_filas, int numero_columnas, const double *ptr_datos = 0){
	int tam = numero_filas*numero_columnas;
	int num_no_nulos = 0, n = 0;

	if (ptr_datos != 0)
		for (int i = 0 ; i < tam ; i++)
			if (ptr_datos[i] != 0.0)
				num_no_nulos++;

	Inicializa(numero_filas, numero_columnas, num_no_nulos);

	if (ptr_datos != 0)
		for (int i = 0 ; i < nfilas ; i++)
			for (int j = 0 ; j < ncolumnas ; j++)
				if (ptr_datos[i*ncolumnas + j] != 0.0){
					valores[n].fila = i;
					valores[n].columna = j;
					valores[n].valor = ptr_datos[i*ncolumnas + j];
					n++;
				}
}

/*	Constructor de copia 	*/
MatrizDispersa::MatrizDispersa (const MatrizDispersa &otra_matriz){
	Inicializa(otra_matriz.nfilas, otra_matriz.ncolumnas, otra_matriz.numeroValores);
	Copia(otra_matriz);
}

/*	Destructor	*/
MatrizDispersa::~MatrizDispersa (){
	Destruir ();
}

/*	Método que recibe como parámetros una fila y columna y devuelve 
	el valor de dicha posición o 0 en caso de no haber valor significativo */
double MatrizDispersa::ObtenerValor (int fila, int columna){
	double valor = 0.0;
	bool encontrado = false;

	for (int i = 0 ; i < numeroValores && !encontrado; i++)
		if (valores[i].fila == fila && valores[i].columna == columna){
			valor = valores[i].valor;
			encontrado = true;
		}

	return valor;
}

/* 	Método que asigna un valor dada una fila y una columna si éste es distinto 
	de 0, o que reduce el número de valores significativos si es igual a 0 	*/
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

/*	Método que combina dos matrices recibidas como parámetro para sumarlas	*/
int MatrizDispersa::CombinarSuma (const MatrizDispersa &matriz_1, const MatrizDispersa &matriz_2){
	double nuevo_valor;
	int numero_valores = 0;

	if (matriz_1.nfilas == matriz_2.nfilas && matriz_1.ncolumnas == matriz_2.ncolumnas){		// Si tienen la misma dimensión
		for (int i = 0 ; i < matriz_1.numeroValores ; i++)			// Se recorren los valores de la primera matriz
			for (int j = 0 ; j < matriz_2.numeroValores ; j++)		// Se recorren los valores de la segunda matriz
				// Si coinciden las posiciones, se suman
				if (matriz_1.valores[i].fila == matriz_2.valores[j].fila &&
					matriz_1.valores[i].columna == matriz_2.valores[j].columna){
					nuevo_valor = matriz_1.valores[i].valor + matriz_2.valores[j].valor;
					AsignarValor (matriz_1.valores[i].fila, matriz_1.valores[i].columna, nuevo_valor);
					numero_valores++;
				}

		AniadirSuma (matriz_1, numero_valores);
		AniadirSuma (matriz_2, numero_valores);
	}

	return numero_valores;
}

/*	Método que produce un nuevo objeto de la clase, mediante la siguiente simplificación:
	todos aquellos valores que estén por debajo de un cierto valor umbral se eliminan 
	(reduciéndose asíı el número de valores almacenados en la matriz). Se valorará la eficiencia del método	*/
void MatrizDispersa::Podar (int valor_umbral){
	int pos_lectura = 0, pos_escritura = 0, eliminados = 0;

	while (pos_lectura < numeroValores){
		if (valores[pos_lectura].valor < valor_umbral){
			pos_lectura++;
			eliminados++;
		}
		else{
			valores[pos_escritura].fila = valores[pos_lectura].fila;
			valores[pos_escritura].columna = valores[pos_lectura].columna;
			valores[pos_escritura].valor = valores[pos_lectura].valor;
			pos_lectura++;
			pos_escritura++;
		}
	}
	Redimensiona(-eliminados);
	numeroValores -= eliminados;
}

/*	Sobrecarga del operador de suma para dos matrices dispersas. Se asume 
	que las matrices sumadas tienen el mismo número de filas y columnas */
MatrizDispersa MatrizDispersa::operator+(const MatrizDispersa &otra_matriz){
	MatrizDispersa resultado;
	int numero_valores = resultado.CombinarSuma(*this, otra_matriz);

	return resultado;
}

/*	Sobrecarga del operador de asignación	*/
MatrizDispersa & MatrizDispersa::operator=(const MatrizDispersa &otra_matriz){
	Destruir ();
	Inicializa(otra_matriz.nfilas, otra_matriz.ncolumnas, otra_matriz.numeroValores);
	Copia(otra_matriz);
	return (*this);
}

/*	Sobrecarga del operador de extracción	*/
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

/*	Sobrecarga del operador de inserción	*/
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

/*	Función que guarda una matriz dispersa en un fichero cuyo nombre se 
	recibe como parámetro y que es introducido en tiemo de ejecución	*/
int Salvar (char *nombre_fich, const MatrizDispersa &matriz){
	ofstream outData;
	outData.open(nombre_fich);
	outData << matriz;
	outData.close();

	return 0;
}

/*	Función que carga una matriz dispersa en un objeto de la clase MatrizDispersa desde un 
	fichero	cuyo nombre se recibe como parámetro y que es introducido en tiemo de ejecución */
int Cargar (char *nombre_fich, MatrizDispersa &matriz){
	ifstream inData;
	inData.open(nombre_fich);
	inData >> matriz;
	inData.close();

	return 0;
}
