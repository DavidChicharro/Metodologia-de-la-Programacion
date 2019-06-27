#ifndef PPAL_FUNC
#define PPAL_FUNC

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
	bool Vacia ();
	void Asigna (int fil, int col, double val);
	
public:
	MatrizDispersa ();
	~MatrizDispersa ();

	void AsignarValor (int fila, int columna, double valor);

	friend ostream& operator<<(ostream &flujo, const MatrizDispersa &matriz);
	friend istream& operator>>(istream &flujo, MatrizDispersa &matriz);
};

ostream& operator<<(ostream &flujo, const MatrizDispersa &matriz);
istream& operator>>(istream &flujo, MatrizDispersa &matriz);

int Salvar (char *nombre_fich, const MatrizDispersa &matriz);


#endif