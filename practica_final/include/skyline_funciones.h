#ifndef SKL
#define SKL

using namespace std;

class SkyLine{
private:
	double *abscisas; 		// abscisas[i] > abscisas[i-1]
	double *alturas;		// alturas[i]>=0 && alturas[n-1] == 0
	int n;					// tamaño de los vectores anteriores

	void Crea ();
	void ReservaMemoria (int tam);
	void Destruye ();
	void Copia(const SkyLine &otro_skyline);
	void Redimensiona ();
	void Simplificar ();
	void MezclarUnico (const SkyLine &skyline_1, const SkyLine &skyline_2);

public:
	SkyLine ();
	SkyLine (double abscisa_1, double abscisa_2, double altura);
	SkyLine (const SkyLine &otro_skyline);
	~SkyLine ();
	double Altura (double abscisa);
	void SetEdificios (double abscisa, double altura);
	void Imprime ();
	SkyLine & operator=(const SkyLine &otro_skyline);
	SkyLine operator+(const SkyLine &skyline_suma);

	friend ostream& operator<<(ostream &flujo, const SkyLine &skyline);
	friend istream& operator>>(istream &flujo, const SkyLine &skyline);
};

ostream& operator<<(ostream &flujo, const SkyLine &skyline);
istream& operator>>(istream &flujo, SkyLine &skyline);

int Salvar (char *nombre_fich, const SkyLine &skyline);
int Cargar (char *nombre_fich, SkyLine &skyline);

#endif