#ifndef MAT_DISP
#define MAT_DISP

using namespace std;

struct Valor {
	int fila;
	int columna;
	double valor;
};

class MatrizDispersa {
private:
	int nfilas;				// Número de filas
	int ncolumnas;			// Número de columnas
	Valor *valores;			// Vector-C no ordenado, solo valores significativos
	int numeroValores;		// Número de valores significativos almacenados

	void Inicializa (int num_filas, int num_columnas, int tam);
	void Destruir ();
	void Redimensiona (int nueva_dim);
	void Copia(const MatrizDispersa &otra_matriz);
	bool Vacia ();
	void AniadirSuma (const MatrizDispersa &matriz, int &numero_valores);
	void Asigna (int fil, int col, double val);
	
public:
	MatrizDispersa ();
	MatrizDispersa (int numero_filas, int numero_columnas, const int v_fila[], const int v_columna[], const double v_valor[], int tamanio);
	MatrizDispersa (int numero_filas, int numero_columnas, const double *ptr_datos);
	MatrizDispersa (const MatrizDispersa &otra_matriz);
	~MatrizDispersa ();

	double ObtenerValor (int fila, int columna);
	void AsignarValor (int fila, int columna, double valor);
	int CombinarSuma (const MatrizDispersa &matriz_1, const MatrizDispersa &matriz_2);
	void Podar (int valor_umbral);

	MatrizDispersa operator+(const MatrizDispersa &otra_matriz);
	MatrizDispersa & operator=(const MatrizDispersa &otra_matriz);

	friend ostream& operator<<(ostream &flujo, const MatrizDispersa &matriz);
	friend istream& operator>>(istream &flujo, MatrizDispersa &matriz);
};

ostream& operator<<(ostream &flujo, const MatrizDispersa &matriz);
istream& operator>>(istream &flujo, MatrizDispersa &matriz);

int Salvar (char *nombre_fich, const MatrizDispersa &matriz);
int Cargar (char *nombre_fich, MatrizDispersa &matriz);

#endif